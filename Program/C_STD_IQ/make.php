<?php
	//$go=$_GET["make"];

	if(strcmp($go,"hash")==0){
			exec(" gcc -m32 -Wall -pedantic -g -o ../out/bin/querydb-hash dataStr/query-with-hash.c dataStr/query-tools.c dataStr/util.c -lm",$a,$v);
			echo "out :";
			print_r($a);
			echo "\n"."stat : ".$v;
	}
	elseif(strcmp($go,"query")==0){
		exec("gcc -m32 -Wall -pedantic -g -o ../out/bin/querydb dataStr/query-with-doclen.c dataStr/query-tools.c dataStr/util.c -lm",$a,$v);
		echo "out :";
		print_r($a);
		echo "\n"."stat : ".$v;
	}
	else{
		echo "nothing";
	}
	// exec("make query",$a,$v);
	// echo "out :";
	// print_r($a);
	// echo "\n"."stat : ".$v;
?>