<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <!-- Tell the browser to be responsive to screen width -->
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">
    <!-- Favicon icon -->
    <link rel="icon" type="image/png" sizes="16x16" href="<?php echo base_url();?>asset/theme/vendor/images/favicon.png">
    <title>MEMOLLAGE</title>
    <!-- Bootstrap Core CSS -->
    <link href="<?php echo base_url();?>asset/theme/vendor/bootstrap-4/css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom CSS -->

    <link href="<?php echo base_url();?>asset/theme/vendor/css/lib/calendar2/semantic.ui.min.css" rel="stylesheet">
    <link href="<?php echo base_url();?>asset/theme/vendor/css/lib/calendar2/pignose.calendar.min.css" rel="stylesheet">
    <link href="<?php echo base_url();?>asset/theme/vendor/css/lib/owl.carousel.min.css" rel="stylesheet" />
    <link href="<?php echo base_url();?>asset/theme/vendor/css/lib/owl.theme.default.min.css" rel="stylesheet" />
    <link href="<?php echo base_url();?>asset/theme/vendor/css/helper.css" rel="stylesheet">
    <link href="<?php echo base_url();?>asset/theme/vendor/css/style.css" rel="stylesheet">
    <link href="<?php echo base_url();?>asset/theme/vendor/css/ml.css" rel="stylesheet">

     <script>
          var BASE_URL = '<?php echo base_url(); ?>index.php/';
          var FLAG_INIT_CHAT=0;
          var FLAG_INIT_NOTIF=0;
     </script>
</head>

<body class="fix-header fix-sidebar" onload="">
    <!-- Preloader - style you can find in spinners.css -->
    <div class="preloader">
        <svg class="circular" viewBox="25 25 50 50">
			<circle class="path" cx="50" cy="50" r="20" fill="none" stroke-width="2" stroke-miterlimit="10" /> </svg>
    </div>
    <!-- Main wrapper  -->
    <div id="main-wrapper">
        <!-- header header  -->
        <div class="header">
            <nav class="navbar top-navbar navbar-expand-md navbar-light">
                <!-- Logo -->
                <div class="navbar-header" style="padding-left: 10px;">
                    <a class="navbar-brand" href="index.html" style="display:flex">
                        <!-- Logo icon -->
                        <b><img src="<?php echo base_url();?>asset/theme/img/Logo.png" alt="homepage" class="dark-logo" width="40" /></b>
                        <!--End Logo icon -->
                        <!-- Logo text -->
                        <span style="margin-top: auto;margin-bottom: auto;"><h5 style="margin-left: 20px;">MEMOLLAGE</h5></span>
                    </a>
                </div>
                <!-- End Logo -->
                <div class="navbar-collapse">
                    <!-- toggle and nav items -->
                    <ul class="navbar-nav mr-auto mt-md-0">
                        <!-- This is  -->
                        <li class="nav-item m-l-10"> <a class="nav-link sidebartoggler hidden-sm-down text-muted" onclick="resizeNav()"  href="javascript:void(0)"><i class="ti-menu"></i></a> </li>

                        <!-- End Messages -->
                    </ul>
                    <!-- User profile and search -->
                    <ul class="navbar-nav my-lg-0">

                        <!-- Search -->
                        <li class="nav-item hidden-sm-down search-box"> <a class="nav-link hidden-sm-down text-muted  " href="javascript:void(0)"><i class="ti-search"></i></a>
                            <form class="app-search">
                                <input type="text" class="form-control" placeholder="Search here"> <a class="srh-btn"><i class="ti-close"></i></a> </form>
                        </li>

                        <!-- Comment -->
                        <li class="nav-item dropdown">
                            <a class="nav-link dropdown-toggle text-muted text-muted" data-value="notif" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> <i class="fa fa-bell"></i>
								<div class="notify"> <span class="heartbit"></span> <span class="point"></span> </div>
							</a>
                            <div class="dropdown-menu dropdown-menu-right mailbox animated zoomIn">
                                 <ul>
                                     <li>
                                         <div class="drop-title">Notifications</div>
                                     </li>
                                     <li>
                                         <div id=notif class="message-center">
                                         </div>
                                    </li>
                                    <li>
                                         <a class="nav-link text-center" href="javascript:void(0);"> <strong>Check all notifications</strong> <i class="fa fa-angle-right"></i> </a>
                                    </li>
                                </ul>
                            </div>
                        </li>
                        <!-- End Comment -->

                        <!-- Messages
                        <li class="nav-item dropdown">
                            <a class="nav-link dropdown-toggle text-muted  " href="#" id="2" data-value="chat" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> <i class="fa fa-envelope"></i>
								<div class="notify"> <span class="heartbit"></span> <span class="point"></span> </div>
							</a>
                            <div id=chat class="dropdown-menu dropdown-menu-right mailbox animated zoomIn" aria-labelledby="2">

                            </div>
                        </li>
                        End Messages


                       Profile -->
                        <li class="nav-item dropdown">
                            <a class="nav-link dropdown-toggle text-muted  " href="#" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><img src="<?php echo base_url()."asset/images/".$resultF->id_foto ?>" alt="user" class="profile-pic" /></a>
                            <div class="dropdown-menu dropdown-menu-right animated zoomIn">
                                <ul class="dropdown-user">
                                    <li><a class="menu" data-value="akun/open" ><i class="ti-user"></i> Profile</a></li>
                                    <li><a href="#" onclick="logout()"><i class="fa fa-power-off"></i> Logout</a></li>
                                </ul>
                            </div>
                        </li>
                    </ul>
                </div>
            </nav>
        </div>
        <!-- End header header -->
        <!-- Left Sidebar  -->
        <div class="left-sidebar">
            <!-- Sidebar scroll-->
            <div class="scroll-sidebar navbar-left">
                <!-- Sidebar navigation-->
                <nav class="sidebar-nav">
                    <ul id="sidebarnav">

                         <li> <a class="menu" data-value="beranda/open"><i class="fa fa-home"></i><span class="hide-menu">Home</span></a></li>
                         <li> <a class="menu" data-value="kelas/open"><i class="fa fa-th-large"></i><span class="hide-menu">Class</span></a></li>
                         <li> <a class="menu" data-value="kalender/open"><i class="fa fa-th-large"></i><span class="hide-menu">Calendar</span></a></li>

                         <!--<li> <a class="menu" data-value="boardChat/open"><i class="fa fa-rocket"></i><span class="hide-menu">chat</span></a></li>
                         -->
                    </ul>
                </nav>
                <!-- End Sidebar navigation -->
            </div>
            <!-- End Sidebar scroll-->
        </div>
        <!-- End Left Sidebar  -->
        <!-- Page wrapper  -->
        <div class="page-wrapper-nav">
            <!-- Bread crumb -->
            <div class="row page-titles">
                <div id=textNav class="col-md-5 align-self-center text-nav">
                    <h3 class="text-primary">Dashboard</h3> </div>
                <div class="col-md-7 align-self-center">
                    <ol class="breadcrumb">
                        <li class="breadcrumb-item"><a href="javascript:void(0)">Home</a></li>
                        <li class="breadcrumb-item active">Dashboard</li>
                    </ol>
                </div>
            </div>
            <!-- End Bread crumb -->
        </div>
        <!-- End Page wrapper  -->
    </div>
    <div class="page-container">
     <div id=page-content class="container">

     </div>
    </div>
    <!-- End Wrapper -->
    <!-- All Jquery -->
    <script src="<?php echo base_url();?>asset/theme/vendor/js/lib/jquery/jquery.min.js"></script>
    <script src="<?php echo base_url();?>asset/theme/vendor/js/lib/bootstrap/js/popper.min.js"></script>

    <!-- Bootstrap tether Core JavaScript -->

    <script src="<?php echo base_url();?>asset/theme/vendor/bootstrap-4/js/bootstrap.min.js"></script>
    <!-- slimscrollbar scrollbar JavaScript -->
    <script src="<?php echo base_url();?>asset/theme/vendor/js/jquery.slimscroll.js"></script>
    <!--Menu sidebar -->
    <script src="<?php echo base_url();?>asset/theme/vendor/js/sidebarmenu.js"></script>




     <script src="<?php echo base_url();?>asset/theme/vendor/js/lib/calendar-2/moment.latest.min.js"></script>
     <!-- scripit init-->
     <script src="<?php echo base_url();?>asset/theme/vendor/js/lib/calendar-2/semantic.ui.min.js"></script>
     <!-- scripit init-->
     <script src="<?php echo base_url();?>asset/theme/vendor/js/lib/calendar-2/prism.min.js"></script>
     <!-- scripit init-->
     <script src="<?php echo base_url();?>asset/theme/vendor/js/lib/calendar-2/pignose.calendar.min.js"></script>
     <!-- scripit init-->
     <script src="<?php echo base_url();?>asset/theme/vendor/js/lib/calendar-2/pignose.init.js"></script>

     <script src="<?php echo base_url();?>asset/theme/vendor/js/lib/owl-carousel/owl.carousel.min.js"></script>
     <script src="<?php echo base_url();?>asset/theme/vendor/js/lib/owl-carousel/owl.carousel-init.js"></script>

     <!-- scripit init-->

     <script src="<?php echo base_url();?>asset/theme/vendor/js/scripts.js"></script>
     <script>
          <?php
               include APPPATH ."modules/notif/ajax/notif.js";
           ?>
     </script>
     <script src="<?php echo base_url();?>asset/theme/vendor/js/header.js"></script>
     <script type="text/javascript">


     </script>
</body>

</html>
