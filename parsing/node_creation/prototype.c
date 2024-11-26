/*

while(token_list)
{
	new_ node = start_node() -> if flag is true creates node and assigns index and sets flag to false, if not it returns NULL
	if(!new_node)
		return(NULL);
	if(detect_unknown || detect_pipe_error || detect_redir_error)
		return(NULL)
	detect_redir();
	detect_cmd_and_args();
	detect_node_end(); -> if token list is a pipe it will set flag and append node
}










 */