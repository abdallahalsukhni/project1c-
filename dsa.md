**Project 1 data structures and algorithms**

<ins>Tushar Kohli and Abdallah Al-Sukhni</ins>

We use a couple data structures. The first and most important is that of `Story`.
A `Story` `struct` encapsulates the information neccessary to uniquely define an 
Instagram ('Insta', hereafter) trending story. That info is thus: its popularity
`score`, `title` and `url`. Our second necessary data structure is an array to 
hold the number of `Stories` (structs) (8) as defined per the top of the given 
story file (`stories.txt`). We dynamically allocate memory for our array using
the `new` keyword and we know much because of this parameter, `storyArrSize`. 
Then we can simply read the input data (stories) into the array, `storyArr`.

Our main algorithm is that to find the mode of the popularity scores of all the
given Insta stories. Implemented in `findMode()`. This function takes in a `const` 
`STORY_ARR` pointer to our array of structs and a `STORY_ARR_SIZE`, size thereof.
Our algo is thus. We first map each story to its associated popularity score. Then,
we check to see if all the modes are the same or not. If there's no difference, or
all modes are the same, that is, then we simply early return -1. If not, we continue,
calculating exactly what this mode of ours is. After calculating this statisical value, 
if there is more than one story with the given mode value then we simply add each of
them to yet another data structure, `modeVector`. Finally! we can find which mode
occurs first in the input file. We break our loop immediately when we find the story 
whose popularity score is equal to our mode and that comes before all the rest. 
We return this value `trueMode`.