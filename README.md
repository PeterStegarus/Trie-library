# Trie
The trie tree was implemented as nodes that hold information and a vector of length 68 (the number of supported characters) of nodes that behave as keys to the following nodes.

There are 2 trees: one for books and one for authors.

# Insert
Adding a book to a tree is done by traversing the tree on the nodes given by the key letters (title/author) and initializing them if they have not yet been assigned. The information is placed in the node given by the last letter.

# Delete
In the case of deletion, if the book to be deleted has been found and if the nodes leading to the deleted book do not lead to any other book, they are recursively deleted. If an author's book tree no longer holds books, Proceed similarly to delete the author from the authors tree.

At the end, go through all nodes in all trees and free all memory allocated.