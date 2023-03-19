<h1>Pizzeria managment app</h1>
<h2>A mini-project to handle a small pizzeria business</h2>
<img src='https://user-images.githubusercontent.com/65015373/226181816-0789b8b7-bf6f-4156-9a92-6a2758dbba3f.png'>



<br>
<hr>
<h2>About it</h2>

<p>The project is build using classes as a homework for object-oriented programming class. It was originally built in romanian language, with function names being written in it, but it has error messages and other stuffs in english. It features 4 classes:</p>
<ul>
    <li>Ingredient</li>
    <li>Pizza</li>
    <li>Angajat (eng. Employee)</li>
    <li>Pizzerie (eng. Pizzeria)</li>
</ul>

<br>
<hr>
<h2>How to use it</h2>

<h3>How to compile</h3>
<code>g++ main.cpp -o main -Wno-write-strings</code>
<br/><br/>

<p>The program has a built in CLI serving for both managering purpose and ordering as a client. All the data are hardcoded via <code>init</code> function.</p>


<br>
<hr>
<h2>Tech specs</h2>

<p>All classes have:</p>
<ul>
    <li>Constructors (empty, coppy, with all parameters, 2-3 parameters </li>
    <li>Deconstructor</li>
    <li>Setters and Getters</li>
    <li>Operator overload:</li>
        <ul>
            <li>++ (pre and post)</li>
            <li>+/- (also implemented as a friend)</li>
            <li>float cast</li>
            <li>logicals (== , <)</li>
            <li><< / >> (ostream version, also compatible with writing to files)</li>
            <li>+ (for adding another class - see Pizzerie class for example )</li>
        </ul>
</ul>

Note! I have used only one file as part of the project requests.
