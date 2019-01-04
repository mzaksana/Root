
// Get the navbar
// var navbar = document.getElementById("header");

function notFound() {

	var a = $.trim($('#off').val());

	var text = "Penelusuran Anda - " + a + " - tidak cocok dengan dokumen apa pun."

	var out = '<section class="face-h">';
	out += '<section>';
	out += '<hgroup>';
	out += '<h1>';
	out += text;
	out += '</h1>';

	out += '<h5>';
	out += "note:";
	out += '</h5>';


	out += '<h5>';
	out += "Aplikasi ini belum mensupport multiple query";
	out += '</h5>';

	out += '<h5>';
	out += "Mendeteksi kata yang mirip dengan query (jika term memang tidak terdapat pada dokumen) ";
	out += '</h5>';

	out += '</hgroup>';
	out += '</section>';
	out += '</section>';


	document.getElementById("searchResult").innerHTML = out;
}


function constructOutput(x) {
	var index;
	var element = document.getElementById("searchResult");
	var tmp = x["info"][0].toString();
	tmp = tmp.split(",");
	var info = tmp[2] + " dokumen ditemukan dari sekitar " + tmp[0] + " term dan " + tmp[1] + " dokumen (" + x["time"][0] + " ms )";
	document.getElementById("time-text").appendChild(document.createTextNode(info));

	if (x["title"].length == 0) {
		notFound();
		return 1;
	}

	for (index = 0; index < x["title"].length; ++index) {

		var section = document.createElement("section");
		var sectionC = document.createElement("section");
		var hgroup = document.createElement("hgroup");

		var h1 = document.createElement("h1");
		var createA = document.createElement('a');
		createA.setAttribute('href', x["url"][index]);

		var h5 = document.createElement("h5");

		var div = document.createElement("div");
		var p = document.createElement("p");

		var text = document.createTextNode(x["content"][index]);
		var texth1 = document.createTextNode(x["title"][index]);
		var texth5 = document.createTextNode(x["url"][index]);

		element.appendChild(section);

		section.appendChild(sectionC);

		sectionC.appendChild(hgroup);
		sectionC.appendChild(div);

		hgroup.appendChild(h1);
		hgroup.appendChild(h5);

		createA.appendChild(texth1);
		h1.appendChild(createA);

		h5.appendChild(texth5);

		div.appendChild(p);
		p.appendChild(text);

		section.classList.add("face-h");
		div.classList.add("desc-web");

	}
}

function send_query(x) {
	var a = $.trim($('#top-r').val());

	$.ajax({
		type: 'POST',
		url: BASE_URL + "searchz/queryz/" + x.toLowerCase() + "/" + a,
		// url: BASE_URL + "search/zquery/" + x.toLowerCase() + "/" + a,

		dataType: "json",

		success: function (data) {
			// alert(4);
			if (data["stat"][0] == 's') {
				console.log(JSON.stringify(data));
				constructOutput(data);
			}
			else {
				console.log(JSON.stringify(data));

				alert(data["stat"][0] + "else send");
			}
		},
		error: function (data) {
			console.log(data);
		}

	});
}

$(document).keypress(
	function (event) {
		if (event.which == '13') {
			var a = $.trim($('#off').val());
			var b = ($('#top-r').val());
			b = parseInt(b, 10);
			if (b == 0 || !Number.isInteger(b)) {
				b = 15;
			}
			if (a) {
				window.location.href = BASE_URL + "searchz?q=" + a.replace(/ /g, "+") + "&z=" + b;
			}
		}
	}
);

$('.top-rank').click(function () {
	// alert($(this).text());
	var a = $.trim($('#off').val());
	$('#top-r').val($(this).text());
	var b = $('#top-r').val();
	b = parseInt(b, 10);
	if (b == 0 || !Number.isInteger(b)) {
		b = 15;
	}
	if (a) {
		window.location.href = BASE_URL + "searchz?q=" + a.replace(/ /g, "+") + "&z=" + b;
	}
});

function load(x) {
	// alert(x);
	send_query(x);
}

$(document).ready(function () {
	result = "";
	load(QUERY);

});


/* When the user scrolls down, hide the navbar. When the user scrolls up, show the navbar */
var prevScrollpos = window.pageYOffset;
window.onscroll = function () {
	var currentScrollPos = window.pageYOffset;
	if (prevScrollpos > currentScrollPos) {
		document.getElementById("navbar").style.top = "0";
	} else {
		document.getElementById("navbar").style.top = "-100px";
	}
	prevScrollpos = currentScrollPos;
}


/* When the user clicks on the button, 
toggle between hiding and showing the dropdown content */
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
