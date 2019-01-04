<?php
	exec("ln -s ../../data data 2>&1",$a,$v);
	echo "out :";
	print_r($a);
	echo "\n"."stat : ".$v;
	// foreach (glob((readlink("./data").'*.*')) as $filename) {
	// 	echo "$filename size " . filesize($filename) . "\n";
	//  }
	//  echo "work hard\n";

	//  echo is_readable("data")."is read\n";
	//  echo is_writable("data")."is write\n";
?>