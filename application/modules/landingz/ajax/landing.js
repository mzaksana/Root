
$(document).keypress(
	function (event) {
		if (event.which == '13') {
			var a = $.trim($('input').val());
			var b = $.trim($('#top-r').val());
			if (b == 0) {
				b = 15;
			}
			if (a) {
				window.location.href = BASE_URL + "searchz?q=" + a + "&z=" + b;
			}
		}
	}
);

$('.top-rank').click(function () {
	var a = $.trim($('input').val());
	$('#top-r').val($(this).text());
	if (a) {
		window.location.href = BASE_URL + "searchz?q=" + a + "&z=" + $(this).text();
		// alert($(this).text());
	}
});


function topS() {
	document.getElementById("myDropdown").classList.toggle("show");
}

// Close the dropdown if the user clicks outside of it
window.onclick = function (event) {
	if (!event.target.matches('.dropbtn')) {
		var dropdowns = document.getElementsByClassName("dropdown-content");
		var i;
		for (i = 0; i < dropdowns.length; i++) {
			var openDropdown = dropdowns[i];
			if (openDropdown.classList.contains('show')) {
				openDropdown.classList.remove('show');
			}
		}
	}
}