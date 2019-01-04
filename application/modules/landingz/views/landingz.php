<!DOCTYPE>
<html>
	<head>

		<link href="<?php echo base_url();?>assets/css/app.css" rel="stylesheet">
		<link href="<?php echo base_url();?>assets/css/attribute.css" rel="stylesheet">
		<link href="<?php echo base_url();?>assets/css/color.css" rel="stylesheet">
		<link href="<?php echo base_url();?>assets/fonts/fontawesome/css/all.css" rel="stylesheet">

		<script type="text/javascript" src="<?php echo base_url();?>assets/vendor/js/jquery-3.3.1.min.js"></script>
		<script>
			var BASE_URL='<?php echo base_url();?>'+"index.php/";
		</script>
        <title>Root</title>
	</head>

	<body class="deep-gray">
		<div class="container">
			<div class="row">
				<div class="content">
					<a href="<?php echo base_url();?>index.php/landingz" ><img href="www.google.com" class="brand" src="<?php echo base_url();?>assets/images/logo.png"></a>
				</div>
				<div class="content">
					<div class="input-search">
					<!-- <form action="../contollers/app.php" method="post"> -->
						<input class="input-type light-gray drop-shadow-lv3 input" type="text" name="query"/>
<!--						<button>seacrh</button>				-->
					<!-- </form> -->
					</div>
				</div>
				<div class="content">
					<div class="input-top-search">
						<input id=top-r class="input-type-nav light-gray drop-shadow-lv3 top" type="text" name="top" value="15"/>
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
				</div>
			</div>
		</div>
		<script type="text/javascript">
			<?php
				include APPPATH ."modules/landingz/ajax/landing.js";
				//include APPPATH ."modules/kelas/ajax/kelasElement.js";
			?>
		</script>
	</body>
</html>