<h1>Server Info Retrieval Program</h1>
<p>This document provides a technical overview of a C++ program designed to retrieve server information, connect to a server, and save server information to a text file. The program uses Winsock for network communication and provides a simple menu-driven interface for user interaction.</p>
<h2>Introduction</h2>
<p>The program primarily utilizes the Winsock library to establish a TCP connection with a specified server. It prompts the user for an IP address and port, validates the IP address, and then presents a menu offering options to display server information, save it to a text file, connect to the server, or exit the program.</p>
<h2>Dependencies</h2>
<ul>
  <li>C++ Standard Library</li>
  <li>Winsock Library (<code>ws2_32.lib</code>)</li>
</ul>
<h2>Functions</h2>
#IsValidIP
<p>This function takes a string representing an IP address and uses a regular expression to validate its format. It returns a boolean indicating whether the IP address is valid.</p>
#DisplayAsciiArt
<p>Displays an ASCII art representation of the program's title.</p>
#GetServerInfo
<p>Establishes a TCP connection with the specified server, sends an HTTP request, and retrieves the server's response. The function returns the server's response as a string.</p>
#DisplayMenu
<p>Displays a simple menu in the console, providing options for the user to interact with the program.</p>
#Main Function
<p>The <code>main</code> function serves as the entry point for the program. It initializes the Winsock library, displays the program's ASCII art title, prompts the user for server details, and enters a loop allowing the user to choose from various options in the menu.</p>
<h2>Usage</h2>
<ol>
  <li>Compile the program, ensuring the Winsock library is linked.</li>
  <li>Run the executable.</li>
  <li>Enter a valid IP address and port.</li>
  <li>Choose an option from the displayed menu.</li>
</ol>
<h2>Conclusion</h2>
<p>This C++ program provides a basic framework for interacting with a server, displaying server information, and connecting to a server using the Winsock library. Users can easily extend and modify the program to suit their specific requirements.</p>




