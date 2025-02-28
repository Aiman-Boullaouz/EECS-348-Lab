function confirmPassword() {
    //Everytime the function runs the amount of attempts is incremented
    attempts++;

    //The user only has two attempts to succesfully input a password
    if (attempts > 2){
        updateField("Exceeded allowed number of attempts...", "red");   //Updates the HTML to alert the user
        return;
    }

    //Getting the passwords from the HTML
    password = document.getElementById("og_password").value;
    confirm_pass = document.getElementById("confirm_pass").value;

    //Checking if the password meets the desired criteria
    if (password.length < 8){
        updateField("Password must be at least 8 digits...", "orange");  //Updates the HTML to alert the user
    }
    else if (password == confirm_pass){
        updateField("Passwords Match!", "green"); //Updates the HTML to alert the user
        attempts = 0;
    }
    else {
        updateField("Passwords do not match...", "orange");             //Updates the HTML to alert the user
    }
}


function updateField(value, color) {
    let field = document.getElementById("alert");   //Gets the HTML tag that is going to be updated
    field.innerHTML = value;                        //changing the value of the HTML
    field.style.color = color;                      //Changing the color of the HTML
}


console.log("Scripts loaded")

var attempts = 0;
document.getElementById("submit_button").addEventListener("click", confirmPassword)
