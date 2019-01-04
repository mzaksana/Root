<?php
	// run("jokowo");
	function trimDoc($line){
		// print ($line);
		$return = array("docno"=>array(),"rank"=>array(),"file"=>array());

		$pos=0;
		$len=0;
		// $tes =strstr($tes,$key);

		$pos=getPosChar($line,"=")+1;
		$line=substr($line,$pos);
		
		$len=getPosChar($line," ");
		$return["docno"]=(int)substr($line,0,$len);

		
		$pos=getPosChar($line,"=")+1;
		$line=substr($line,$pos);
		
		$len=getPosChar($line," ");
		$return["rank"]=(double)substr($line,0,$len);

		$pos=getPosChar($line,"=")+1;
		$line=substr($line,$pos);
		// $len=getPosChar($line," ");
		$return["file"]=substr($line,0);
	
		return $return;
		
		
		// echo $return["docno"]=substr($line,$pos);
	}
#List docno=48 doc_rank=2.355992
	function getPosChar($line,$trim){
		return strlen($line)-strlen(strstr($line,$trim));
	}

	function getTime($line){
		$pos=0;
		$len=0;
		// $tes =strstr($tes,$key);

		$pos=getPosChar($line,"=")+1;
		$line=substr($line,$pos);

		$len=getPosChar($line," ");

		return substr($line,0,$len);
	}

	function getInfo($line){
		$return = array("term"=>array(),"doc"=>array());

		$pos=getPosChar($line,"=")+1;
		$line=substr($line,$pos);
		
		$len=getPosChar($line," ");
		$return["term"]=(int)substr($line,0,$len);

		
		$pos=getPosChar($line,"=")+1;
		$line=substr($line,$pos);
		
		$len=getPosChar($line," ");
		$return["doc"]=(double)substr($line,0,$len);

		return $return;
	}

	function getDocFound($line){
		// $return = array("term"=>array(),"doc"=>array());

		$pos=getPosChar($line,"=")+1;
		$line=substr($line,$pos);
		
		$pos=getPosChar($line,"=")+1;
		$line=substr($line,$pos);

		// $len=getPosChar($line," ");
		return (int)$line;

		// return $return;
	}

	function run($query,$top){
		// $query=sprintf("Program/out/bin/querydb-hash %s 2>&1",$_POST["query"]);
		$query=sprintf("Program/out/bin/querydb-hash %s %d 2>&1",$query,$top);
		$return = array("info"=>array(),"docno"=>array(),"rank"=>array(),"file"=>array(),"flag"=>array(),"time"=>array());


		// 'bash -c "exec nohup setsid your_command > /dev/null 2>&1 &"'
		// $a = array();
		// $rv=0;
		// exec('bash -c "exec nohup setsid ../../out/bin/querydb-hash > /dev/null 2>&1 &"',$a,$rv);
		
		exec("$query",$a,$rv);

		if(sizeof($a)<3){
			array_push($return["flag"],"notFound qry : ".$query." stat: ".$rv." out : ".implode($a)." dir : ".getcwd());
			return $return;
		}
		array_push($return["flag"],"Found");
		
		$info = getInfo($a[0]);
		array_push($return["info"],$info["term"]);
		array_push($return["info"],$info["doc"]);

		array_push($return["info"], getDocFound($a[1]));

		
		for ($i=3; $i <sizeof($a)-1 ; $i++) { 
			$tmp=trimDoc($a[$i]);
			array_push($return["docno"],$tmp["docno"]);
			array_push($return["rank"],$tmp["rank"]);
			array_push($return["file"],$tmp["file"]);
		}
		
		$time=getTime($a[sizeof($a)-1]);
		array_push($return["time"],$time);

		// print_r($return);
		// echo json_encode($return);
		
		return $return;
		// foreach ($a as $key => $value) {
		// 	echo $value;
		// 	echo "<br />\n";
		// }
		// $b=$a[0];
		// echo $a[4]."\n";
		// echo $rv."\n";
		// echo getcwd();
		// echo is_writable(dirname("/var/www/html/proPi/src/c"));
		// if($rv!=0)
		// {
		// die("readcard failed, got a return value of $rv\n");
		// }
		// echo sizeof($a);
		// echo $a[0];
		// foreach ($a as $key => $value) {
		// 	echo $value."\n";
		// }
		//	echo $_SERVER['SERVER_NAME'];

		// $output=array();
		// $rv=0;
		// exec('../../out/bin/querydb-hash jokowi',$output,$rv);

		// if($rv!=0)
		// {
		// die("readcard failed, got a return value of $rv\n");
		// }

		// foreach($output as $line)
		// {
		// echo $line."\n";
		// }
	}
?>



