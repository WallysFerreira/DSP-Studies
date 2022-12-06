# Bookmark
<p> Chapter 1.7.4 | 172 no PDF | 145 no Livro </p>


# Breakpoints

## Function to read breakpoints from a file
<p><strong>Goal of the file:</strong> Find 2 numeric informations (time and value) on each line of a file, store those informations in an array of structure BREAKPOINT and return the array</p>

### Function receives:
<ul>
  <li>File it is going to read from as a pointer to type FILE</li>
  <li>The amount of points that have been read in total at the main function. That amount is set by this function, so it needs to be a pointer to type int</li>
</ul>

### Nice to know:
<p><strong>fgets</strong>(string to temporarily store the line it is going to read, maximum number of characters to read in a line, file to read from)
<br>
<strong>fgets</strong> returns NULL when there are no lines to read anymore or when an error occurs.</p>

<p><strong>sscanf</strong>(string to temporarily store the line it is going to read, format specifier to search in the line, addresses to store the information it found)
<br>
<strong>sscanf</strong> returns the amount of information it has read. If it returns a negative number, the line was empty</p>

<p><strong>malloc use template</strong>
<br>
receiveMemory = (type of receiveMemory) malloc(sizeof(type of receiveMemory) * spacesToAllocateMemoryFor)
<br>
<strong>Remember receiveMemory has to be a pointer</strong></p>

<p><strong>realloc use template</strong>
<br>
temporary = (type of receiveMemory) realloc(receiveMemory, sizeof(type of receiveMemory) * spacesToAllocateMemoryFor)
<br>
<strong>Remember receiveMemory and temporary has to be a pointer</strong></p>