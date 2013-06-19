<?php
/**
 * Define the ArtworkQuery class
 */
class ArtworkQuery extends EntityFieldQuery {

	// a public property storesthe EntityFieldQuery (efq) query result
	public $efq_result;

	// public property stores the processed artwork objects
	public $artworks = array();

	// public property stores the field_names required in the query
	// this array is structured as follows: array('field_name' => 'field_key')
	public $required_data;

	/**
	 * apply some defaults to all instances of this object
	 */
	public function __construct($required_data = array(), $start = 0, $length = 30) {

		// set the required fields
		$this->required_data = $required_data;

		$this
			// we're interested in ARTWORK NODES
			->entityCondition('entity_type', 'node')
			->entityCondition('bundle','artwork')
			// Default to published
			->propertyCondition('status', 1)
			// define a default range for the query
			// starting at 0 and ending in 20
			->range( $start , $length );
	}

	/**
	 * Override the default 'execute()' method.
	 */
	public function execute() {
		// call parent "execute()" method.
		$this->efq_result = parent::execute();


		// with the response of the parent execute query, 
		// extract required fields.
		if ( isset($this->efq_result['node']) && count($this->efq_result['node']) > 0 ) {
			// if there are any results,

			$nids = array_keys($this->efq_result['node']);

			// load all necessary nodes
			$nodes = node_load_multiple($nids);

			foreach ($nodes AS $node) {
				// build the artwork object, which is just an understandable version
				// of whatever bullshit comes from the $node.
				// The instantiation of a new ArtworkObj processes the required_fields

				$artwork = new ArtworkObj($node, $this->required_data);

				// only add the artwork if it has an image
				if ( isset($artwork->images) && isset($artwork->images['original']) ) {

					array_push($this->artworks, $artwork);
				}
			}

			// return the artworks array.
			return $this->artworks;

		} else {
			// no results, return a message
			return NULL;
		}
	}

}


// this class just processes data from the node and returns the required data.
// it always returns the nid of the artwork.
class ArtworkObj {

	public function __construct($node, $required) {
		// $required is an array containing 2 keys: fields and properties.


		// get the required properties for the node and store
		// them in public properties
		if ( isset($required['properties']) ) {

			// check if in the required fields the nid is already requested.
			// if so, do nothing. Else, add the nid to the required properties
			if ( !isset($required['properties']['nid']) ) {
				$required['properties']['nid'] = array('alias' => 'id');
			}

			foreach ($required['properties'] AS $property_name => $info) {
				$this->{$info['alias']} = $node->{$property_name};
			}
		}

		// get the required fields for the node and store 
		// them in public properties of the new object.
		if ( isset($required['fields']) ) {
			foreach ($required['fields'] AS $field_name => $info) {
				// field_get_items just processes the value inside the $node object. 
				// It does not do a request to the database, because the node has already been loaded.
				$field_values = $this->get($node, $field_name, $info);
				
			}
		}
	}

	// the ain value getter.
	// this method chooses the right getter method to be run.
	public function get($node, $field_name, $info) {

		$type = isset($info['type']) ? $info['type'] : 'default';

		if ($type == 'default') {

			return $this->get_default($node, $field_name, $info);

		} else {
			switch($type) {
				case 'image':
					return $this->get_image($node, $field_name, $info);
					break;

				case 'entityreference':
					return $this->get_entityref($node, $field_name, $info);
					break;


				default: 
					return $this->get_default($node, $field_name, $info);
					break;
			}
		}
	}

	// DEFINE VALUE GETTERS:

	// images!
	public function get_image($node, $field_name, $info) {

		// the styles to get
		$styles = $info['styles'];


		$field_values = field_get_items('node', $node, $field_name);


		$images = array();

		if (count($field_values) > 0) {
			foreach ($field_values as $key => $value) {

				// build all image size requested.
				foreach ($styles AS $style) {
					$url = image_style_url($style, $value['uri']);

					$images[ $style ] = $url;
				}

				// build the url to the original image.
				// this happens after all requested image styles are set,
				// because this way, it can override another 'original' image style.
				$images['original'] = file_create_url($value['uri']);
			}
		}

		$this->{$info['alias']} = $images;
	}

	// entity references
	public function get_entityref($node, $field_name, $info) {

		$required_entity_fields = $info['required_entity_fields'];
		$field_values = field_get_items('node', $node, $field_name);

		$this->{$info['alias']} = array();

		if (count($field_values) > 0) {
			foreach ($field_values as $key => $value) {
				$id = $value[ 'target_id' ];

				$node = node_load($id);

				foreach ($required_entity_fields as $field_name) {
					$this->{$info['alias']}[$field_name] = $node->{$field_name};
				}

				// force add the id field.
				$this->{$info['alias']}['nid'] = $node->nid;
			}
		}


	}

	// defaults
	public function get_default($node, $field_name, $info) {
		$field_values = field_get_items('node', $node, $field_name);

		if (count($field_values) > 1) {
			// if the field has more than 1 value,
			// return an array with the values
			$this->{$info['alias']} = array();

			foreach($field_values AS $v) {
				array_push( $this->{$info['alias']}, $v[ $info['key'] ] );
			}
		} else {
			// else return the value directly.
			$this->{$info['alias']} = $field_values[0][ $info['key'] ];
		}
	}
}