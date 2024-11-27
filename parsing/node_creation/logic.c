/*

while token++
{
	1. Check unknown token and pipe error (bool)
		returns true if it finds uknown token (symbol outside quotes)
		returns true if it finds pipe at start/end or pipe followed by another pipe

	2. Grab_node (bool)
		will create and allocate nodes, if something fails it returns null
		Here this happens:

		2.1. IF node_starts = true (bool) Node init
			 - Will create a new node and return false if mem alloc failed

		2.2. IF we encounter pipe (void) End node
				- Resets node_starts and cmd_found to their initial bool value
				- Appends the ended new node to the nodelist (void)
		2.3. ELSE Handles redirs, cmd and args data
			 	- Changes node_starts to false so we can hit this condition until we find pipe ans end node to reset flag
					2.3.1. IF token is of redirection type
						-IF return false if add redir function fails
						-jump to the next token (arg or cmd)

					2.3.2 ELSE



}





// node init, returns new node,if failes it is null
// end node - ends the current node, appends it to the list, start_node flag and cmd_flag
void append_node(t_node **head, t_node *new_node); // apends current node to list as head or last





 */
