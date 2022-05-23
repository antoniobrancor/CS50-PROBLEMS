function darkMode() {
    var element = document.body;
    var content = document.getElementById("DarkModetext");
    element.className = "dark-mode";
    localStorage.setItem("darkMode", "enabled");
}

function lightMode() {
    var element = document.body;
    var content = document.getElementById("DarkModetext");
    element.className = "light-mode";
    localStorage.setItem("darkMode", "disabled");
}

$(document).ready(function () {
    var sidenavcontainer = $("#sidenav-container");
    sidenavcontainer.load("./sidenav.html");

    var darkModeEnabled = localStorage.getItem("darkMode");
    if (darkModeEnabled == "enabled") {
        darkMode();
    }
});

