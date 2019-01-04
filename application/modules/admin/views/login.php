<!DOCTYPE>
<html>
	<head>

		<link href="<?php echo base_url();?>assets/css/app.css" rel="stylesheet">
		<link href="<?php echo base_url();?>assets/css/attribute.css" rel="stylesheet">
		<link href="<?php echo base_url();?>assets/css/color.css" rel="stylesheet">
		<link href="<?php echo base_url();?>assets/fonts/fontawesome/css/all.css" rel="stylesheet">

		<script type="text/javascript" src="<?php echo base_url();?>assets/vendor/js/jquery-3.3.1.min.js"></script>
		<script>
			var BASE_URL='<?php echo base_url();?>';
		</script>
        <title>Root</title>
	</head>

	<body class="deep-gray">
		<div class="container">
			<div class="row">
				<div class="content">
					<a href="<?php echo base_url();?>" ><img href="www.google.com" class="brand" src="<?php echo base_url();?>assets/images/logo.png"></a>
				</div>

				<div class="content">
					<div class="input-bar">
						<form id="fromLog">
							<input class="input-type-login light-gray drop-shadow-lv3" type="text" name="email" placeholder="email"/>
							<input class="input-type-login light-gray drop-shadow-lv3" type="text" name="password" placeholder="password"/>
							<button class=login-act> Login </button>
						</form>
					</div>
					
				</div>
			</div>
		</div>

		<script type="text/javascript">
			<?php
				include APPPATH ."modules/admin/ajax/login.js";
				//include APPPATH ."modules/kelas/ajax/kelasElement.js";
			?>
		</script>
	</body>
</html>