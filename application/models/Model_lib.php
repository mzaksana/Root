<?php

class Model_lib extends CI_Model {

    function __construct() {
        // Call the Model constructor
        parent::__construct();
    }

    function SelectWhere($table,$where)
    {
         $query=$this->db->query("select *from $table $where");
         return $query;
    }
    function insert($tabel,$data)
    {
        $query=$this->db->insert($tabel, $data);
        return $query;
    }

}

?>
