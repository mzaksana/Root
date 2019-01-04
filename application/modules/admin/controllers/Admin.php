<?php
defined('BASEPATH') OR exit('No direct script access allowed');

class Admin extends CI_Controller {

	/**
	 * Index Page for this controller.
	 *
	 * Maps to the following URL
	 * 		http://example.com/index.php/welcome
	 *	- or -
	 * 		http://example.com/index.php/welcome/index
	 *	- or -
	 * Since this controller is set as the default controller in
	 * config/routes.php, it's displayed at http://example.com/
	 *
	 * So any other public methods not prefixed with an underscore will
	 * map to /index.php/welcome/<method_name>
	 * @see https://codeigniter.com/user_guide/general/urls.html
	 */

     function __construct() {
		parent::__construct();
		// $this->_public_view= $this->config->item('public_view');
          //$this->load->helper('url');
		$this->load->model('Model_lib');
	}

	public function index()
	{
		// $data=array('page_content' => 'landing');
		if($this->session->userdata('email') == '') {
			$this->load->view("login");
		}else{
			$this->load->view("admin");
		}
	}


	function login()
     {

		$data["email"] = $this->db->escape_str($this->input->post("email"));
		$data["password"] = stripslashes($this->db->escape_str($this->input->post("password")));

  		if(empty($data['email']))
	    	{
		    $err="Mohon isi alamat email";
	    	    $klas="#email";
	    	    $param="";
	    	}
	    	else  if(!filter_var($data['email'], FILTER_VALIDATE_EMAIL)) {
	    	    $err="Email yang anda masukkan tidak valid";
	    	    $klas="#email";
	    	    $param="";
          }
	    	else if(empty($data["password"]))
	    	{
	    	    $err="Mohon isi password";
	    	    $klas="#password";
	    	    $param="";
	    	}
	    	else
	    	{
			$where=sprintf("WHERE email='%s'",$data["email"]);			
			$resultF = $this->Model_lib->SelectWhere("admin",$where)->row();
			if($resultF==1){
				$where=sprintf("WHERE email='%s' AND pass='%s'",$data["email"],$data["password"]);			
				$resultF = $this->Model_lib->SelectWhere("admin",$where)->row();
				$err="s";
				$klas="";
				$this->session->set_userdata("email",$data["email"]);
			}else{
				$err="email tidak terdaftar";
				$klas="#email";
				$param="";
			}
	     }
	    		$arr = array('err'=>$err,'klas'=>$klas);
	    echo json_encode($arr);
     }

     function logout(){
          $this->session->unset_userdata("akun");
          $this->session->unset_userdata("table");
          $this->session->unset_userdata("data");
     }

}
