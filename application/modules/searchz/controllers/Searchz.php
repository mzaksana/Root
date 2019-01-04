<?php
defined('BASEPATH') OR exit('No direct script access allowed');

class Searchz extends CI_Controller {

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
		// $this->load->model('Model_lib');
	}

	public function index()
	{
		// $data=array('page_content' => 'landing');
		$this->load->view("searchz");
	}

	public function query($query,$top){
		// print($query);
		// ob_start();
		$return = array('stat'=>array(),'url' => array(),'title' => array(),'content' => array(),"time"=>array(),"info"=>array(),"rank"=>array());
		
		require_once("Program/C_STD_IQ/run.php");
		$return["time"][0]=0;
		$arrayQuery = explode("%20", $query);
		foreach ($arrayQuery as $key => $valueQuery) {
			$content = run($valueQuery,$top);
			// print_r($content );
			// ob_end_clean();
			// print_r($content);
			// print_r( $this->getTitle($content["file"][0]));


			$DIR="Program/data/";
			// $DIR="/media/zx/Pro/crawl/data/";
			if(strcmp($content["flag"][0],"Found")==0){
				for ($i=0; $i <sizeof($content["docno"]) ; $i++) { 
					
					$dom=$this->getFile($DIR,$content["file"][$i])."\n";
					array_push($return["url"],$this->getUrl($dom));
					array_push($return["title"],$this->getTitle($dom));
					array_push($return["content"],$this->getContent($dom));
					array_push($return["rank"],$content["rank"]);
					// echo $this->getContent($content["file"][$i])."\n";
				
				}

				$return["time"][0]=number_format($return["time"][0]+$content["time"][0],4);
				array_push($return["info"],$content["info"]);
				array_push($return["stat"],"s");
			}else{
				$v="<h1>";
				$v.="tidak ditemukan";
				$v.=$content["flag"][0];
				$v.="</h1>";
				array_push($return["stat"],$v);
			}
		}
		
		// echo ($content);
		// print_r($return);
		// print_r($content["file"][0]);
		
		echo json_encode($return);
	}

	public function queryz($query,$top){
		// print($query);
		// ob_start();
		$return = array('stat'=>array(),'url' => array(),'title' => array(),'content' => array(),"time"=>array(),"info"=>array(),"rank"=>array());
		
		require_once("Program/C_STD_IQ/service.php");
		$return["time"][0]=0;
		$arrayQuery = explode("%20", $query);
		foreach ($arrayQuery as $key => $valueQuery) {
			$content = run($valueQuery,$top);
			// print_r($content );
			// ob_end_clean();
			// print_r($content);
			// print_r( $this->getTitle($content["file"][0]));


			$DIR="Program/data/";
			// $DIR="/media/zx/Pro/crawl/data/";
			if(strcmp($content["flag"][0],"Found")==0){
				for ($i=0; $i <sizeof($content["docno"]) ; $i++) { 
					
					$dom=$this->getFile($DIR,$content["file"][$i])."\n";
					array_push($return["url"],$this->getUrl($dom));
					array_push($return["title"],$this->getTitle($dom));
					array_push($return["content"],$this->getContent($dom));
					array_push($return["rank"],$content["rank"]);
					// echo $this->getContent($content["file"][$i])."\n";
				
				}

				$return["time"][0]=number_format($return["time"][0]+$content["time"][0],4);
				array_push($return["info"],$content["info"]);
				array_push($return["stat"],"s");
			}else{
				$v="<h1>";
				$v.="tidak ditemukan";
				$v.=$content["flag"][0];
				$v.="</h1>";
				array_push($return["stat"],$v);
			}
		}
		
		// echo ($content);
		// print_r($return);
		// print_r($content["file"][0]);
		
		echo json_encode($return);
	}

	function getFile($DIR,$file){
		$data = file_get_contents($DIR.$file);
		// echo "data :".$data;
		// $content =  preg_replace("/\[(.*?)\]\s*(.*?)\s*\[\/(.*?)\]/", "[$1]$2[/$3]", html_entity_decode($data));
		// $content = preg_replace('/\s+/', ' ', $content);
		// $content = str_replace("&nbsp", '', $content);
		// $content = trim($content);
		// echo  $content;
		return $data;
	}
	
	function getUrl($file){

		$url = preg_match('<!-- url=(.*?)-->', $file, $matches) ? $matches[1] : null;
		// $url = preg_replace('/\s+/', ' ', $url);
		// $url = str_replace("&nbsp", '', $url);
		// $url = preg_replace('/[^A-Za-z0-9 \-]/', '', $url);
		// $url = trim($title);
		   
		return $url;
	}

	function getTitle($file){

		$title = preg_match('/<title[^>]*>(.*?)<\/title>/siU', $file, $matches) ? $matches[1] : null;
		$title = preg_replace('/\s+/', ' ', $title);
		$title = str_replace("&nbsp", '', $title);
		$title = preg_replace('/[^A-Za-z0-9 \-]/', '', $title);
		$title = trim($title);
		   
		return $title;
	}

	function getContent($file){

		$content = preg_match('/<content[^>]*>(.*?)<\/content>/siU', $file, $matches) ? $matches[1] : null;
		$content = preg_replace('/\s+/', ' ', $content);
		$content = str_replace("&nbsp", '', $content);
		$content = preg_replace('/[^A-Za-z0-9 \-]/', '', $content);
		$content = trim($content);
				
		return $this->cutContent($content);
	}
	 
	function cutContent($content){
		$arr=explode(" ",$content);
		$newContent="";

		if(count($arr)>=25){
			for ($i=0; $i < 25; $i++) {
				$newContent .= " ".$arr[$i];
			}
		}

		else{
			return $content;
		}

		return $newContent."...";
	}
}
