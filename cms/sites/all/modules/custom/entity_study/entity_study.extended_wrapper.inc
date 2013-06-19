<?php

/**
 * Defines an ExtendedEntityMetadataWrapper
 */
class ExtendedEntityMetadataWrapper  {

	// constructor 
	public function __construct($entity_type, $entity) {
		$this->wrapper = entity_metadata_wrapper($entity_type, $entity);
	}

	// Forward all requests for not found objects to the wrapper object.
	public function __get($prop) {
		return $this->wrapper->{$prop};
	}

	// Intercept all calls to methods not found on this object
	// and forward them to the wrapper object.
	public function __call($name, $arguments) {
		// forward the method calling
		return call_user_func_array(array($this->wrapper, $name),$arguments);
	}


	// set method
	public function set($prop, $value, $force = TRUE) {
		// $prop: the name of the property tobe set on the wrapper
		// $value: the value to be set to. might be array or string
		// $force: is used in case the $value format does not fit the $prop format requirements
		//			in that case, if $force is set to true, the value will be modified to fit in


	}
	
	// method that determines if a given field receives signle or multiple values
	public function field_data_format($field_name) {
		$answer = array();

		$finfo = field_info_field($field_name);

		if ( isset($finfo) && count($finfo) > 0 ) {

			$answer['is_field'] = TRUE;

			$answer['field_info'] = $finfo;
			$answer['is_single'] = ($finfo['cardinality'] == 1);
			$answer['type'] = $finfo['type'];

		} else {
			// if there is no field info, that means the requested field 
			// is actually a property
			$answer['is_field'] = FALSE;

			$answer['field_info'] = NULL;
			$answer['is_single'] = TRUE;

		}

		return $answer;
	}
}