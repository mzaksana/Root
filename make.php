<?php
	$go=$_GET["make"];

	if(strcmp($go,"server")==0){
		exec(" gcc -m32 -Wall -std=gnu99 -o Program/C_STD_IQ/service/out/server Program/C_STD_IQ/service/server.c -lm",$a,$v);
		echo "out :";
		print_r($a);
		echo "\n"."stat s: ".$v;
	}
	elseif(strcmp($go,"client")==0){
		exec("gcc -m32 -Wall -std=gnu99 -o Program/C_STD_IQ/service/out/client Program/C_STD_IQ/service/client.c -lm",$a,$v);
		echo "out :";
		print_r($a);
		echo "\n"."stat e: ".$v;
	}
	else{
		echo "nothing";
	}
	// exec("make query",$a,$v);
	// echo "out :";
	// print_r($a);
	// echo "\n"."stat : ".$v;
?>