let task = "factor";

function doPrimalityTest(e) {
    if(task == "check-primality") return;

    task = "check-primality";
    document.querySelector("button").textContent = "check";
    switchOption(e.currentTarget);
}

function doFactoring(e) {
    if(task == "factor") return;

    task = "factor";
    document.querySelector("button").textContent = "factor";
    switchOption(e.currentTarget);
}

/**
 * switches option to another
 * @param other - the option we are switching to
 */
function switchOption(other) {
    let current = document.querySelector(".optionActive");
    // turn off current option
    if(current)
    {
        current.classList.remove("optionActive");
        current.classList.add("optionInactive");
    }

    // turn on other option
    other.classList.remove("optionInactive");
    other.classList.add("optionActive");

    // clear result
    document.querySelector("#result").textContent = "---";
}

/**
 * input submision
 */
document.querySelector("form").addEventListener("submit", function(e) {
    let data = document.querySelector("#inputNumber").value;

    const xhr = new XMLHttpRequest();

    xhr.open("POST", "http://192.168.178.227:5000/" + task, true);
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function() {
        let output;
        if (xhr.readyState === 4 && xhr.status === 200) {
            output = xhr.responseText;
            if(task == "factor") {
                output = output.slice(0, -1);
                output = output.replaceAll("\n", " \u00B7 ");
            }
        }
        else {
            output = "server error";
        }
        document.querySelector("#result").textContent = output;
    };
    xhr.send(data);

    e.preventDefault();
});

function isDigit(e) {
    e = (e) ? e : window.event;
    var charCode = (e.which) ? e.which : e.keyCode;
    if (charCode < 31 || (charCode >= 48 && charCode <= 57)) return true;
    return false;
}