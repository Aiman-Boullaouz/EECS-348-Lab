function updateColor() {
    //Getting variables values from the HTML
    var red_val = document.getElementById("red").value;
    var green_val = document.getElementById("green").value;
    var blue_val = document.getElementById("blue").value;

    //Creating our RBG value using a string
    var color = 'rgb(' + red_val + ',' + green_val + ',' + blue_val + ')';

    //Updating the target elements color
    document.getElementById("target").style.color = color;
    document.getElementById("target").style.outlineColor = color;

    //Using this to confirm that my functions are running as expected
    console.log("Update color ran");
    console.log(color);
}

function updateBorder() {
    //Getting the input from the HTML
    var border_val = document.getElementById("border").value;

    //Updating the target element's border
    document.getElementById("target").style.outlineWidth = border_val+"px";

    //Confirming functions are running
    console.log("update border ran");
    console.log(border_val);
}

//Confirm the JS file has connected
console.log("JS File Connected")

//Using event listeners to react to user inputs
document.getElementById("red").addEventListener("input", updateColor);
document.getElementById("green").addEventListener("input", updateColor);
document.getElementById("blue").addEventListener("input", updateColor);
document.getElementById("border").addEventListener("input", updateBorder);