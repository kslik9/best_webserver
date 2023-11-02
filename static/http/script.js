function clickMe() {
    if (document.getElementById("title").innerHTML != "WAAAAA3")
    {
        document.getElementById("title").innerHTML = "WAAAAA3";
        document.getElementById("3iniha").innerHTML = "3iniha mla7"
    }
    else
        document.getElementById("title").innerHTML = "Default Index Lmli7";
}

document.getElementById("butona").addEventListener("click", clickMe);