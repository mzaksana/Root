<?php
	
	// exec("unlink  /home/mksana/public_html/Program/data",$a,$v);
	// echo "out :";
	// print_r($a);
	// echo "\n"."stat : ".$v;

	// exec("ln -s ../data ./Program/data 2>&1",$a,$v);
	// echo "out :";
	// print_r($a);
	// echo "\n"."stat : ".$v;

	// echo readlink("Program/data");
	// echo is_readable(readlink("/var/www/html/proPi/src/c"));
	//$data = file_get_contents("Program/data/liputan6-bola-5274.tt",FALSE, NULL, 0, 36);
	
	foreach (glob((readlink("./Program/data/").'*.*')) as $filename) {
		$v="$filename size " . filesize($filename) . "\n";
	}
	echo "work hard";

	// echo readlink('Program/data/');
?>