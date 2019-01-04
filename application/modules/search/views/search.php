<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<title>Root</title>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link href="<?php echo base_url();?>assets/fonts/fontawesome/css/all.css" rel="stylesheet">
	<script type="text/javascript" src="<?php echo base_url();?>assets/vendor/js/jquery-3.3.1.min.js"></script>
	<script>
		var BASE_URL='<?php echo base_url();?>'+"index.php/";
		var QUERY='<?php echo $_GET["q"];?>';
		// alert(QUERY);
	</script>
</head>
<body>

	<header id="navbar" class="deep-gray drop-shadow-lv3">
		<div class="logo-nav">
			<a href='<?php echo base_url();?>' class="link">
				<img class="brand-nav" src="<?php echo base_url();?>assets/images/logo.png">
			</a>
		</div>

		<div class="input-nav">
				<input id=off class="input-type-nav light-gray drop-shadow-lv3 input" type="text" name="query" value='<?php echo $_GET["q"]?>'/>
		</div>

		<div class="input-top">
				<input id=top-r class="input-type-nav light-gray drop-shadow-lv3 top" type="text" name="top" value='<?php echo $_GET["z"]?>'/>
		</div>
		<div class="dropdown">
			<button onclick="topS()" class="dropbtn"><i class="fas fa-sort"></i></button>
	
			<div id="myDropdown" class="dropdown-content">
				<a href="#" class="top-rank">10</a>
				<a href="#" class="top-rank">20</a>
				<a href="#" class="top-rank">30</a>
				<a href="#" class="top-rank">40</a>
				<a href="#" class="top-rank">50</a>
				<a href="#" class="top-rank">100</a>
			</div>
		</div>
	</header>

	<section id="time" class="report">
		<!-- 2 ditemukan dari sekitar 1.910.000.000 dokumen (0,42 detik) -->
		<h5 id="time-text"></h5>
	</section>

	<div id="searchResult" class="container-face center">
			
	</div>


	<script type="text/javascript">
		<?php
			include APPPATH ."modules/search/ajax/search.js";
			//include APPPATH ."modules/kelas/ajax/kelasElement.js";
		?>
	</script>


	<link href="<?php echo base_url();?>assets/css/app.css" rel="stylesheet">
	<link href="<?php echo base_url();?>assets/css/attribute.css" rel="stylesheet">
	<link href="<?php echo base_url();?>assets/css/color.css" rel="stylesheet">
	<link href="<?php echo base_url();?>assets/css/effect.css" rel="stylesheet">

</body>
</html>