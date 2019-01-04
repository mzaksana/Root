$('.login-act').click(function () {
	$.ajax({
		type: "POST",
		//url: 'http://localhost/memollage/index.php/signUp/proses_simpan',
		url: BASE_URL + 'admin/login',
		data: $('#fromLog').serialize(),
		dataType: "json",
		success: function (data) {
			if (data.err == 's') {
				alert(data.err);
				window.open(BASE_URL + 'admin', "_self");
			} else {
				alert(data.err);
				$(data.klas).focus();
			}
		},
		error: function (data) {
			alert(data.err);
		}
	});
});