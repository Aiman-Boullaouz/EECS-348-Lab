//Alright, full disclosure, I couldn't figure out how to run PHP on my device so I am
//just completing this whole section in JavaScript... apologies

function createTable(){

    var num = parseInt(document.getElementById('num').value);

    //Making a label for the table
    var table = "<h4>Created " + num + " x " + num + " Multiplication Table</h4>";

    //creating the table
    table += "<table>";

    //Creating the indices in the Table
    table += "<tr><th>&times;</th>";
    for (var col = 1; col <= num; col++) {
        table += "<th>" + col + "</th>";
    }
    table += "</tr>";

    //Creating the rows in the table
    for (var row = 1; row <= num; row++) {
        table += "<tr><th>" + row + "</th>";
        
        //Creating the columns in the table
        for (var col = 1; col <= num; col++) {
            table += "<td>" + (row * col) + "</td>";
        }
        table += "</tr>";
    }

    table += "</table>";    //Closing the table

    // Inserting the table into the html
    document.getElementById('output').innerHTML = table;
}


console.log("Script loaded")

//Waiting for the user to put in a number and click submit
document.getElementById("submit").addEventListener("click", createTable)