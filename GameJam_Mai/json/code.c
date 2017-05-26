
void get_json(filename){
	JsonParser *parser
	GError *error;
	JsonNode *root;
	JsonReader *reader;
	
	parser = json_parser_new();
	
	error = NULL;
	json_parser_load_from_file(parser, filename, &error);
	if(error){
		g_print("unable to parse: %s", error->message);
		return;
	}
	
	root = json_parser_get_root(parser);
	
	/* use object tree */
	
	reader = json_reader_new(root);
	
	JsonNode *tmp_node;
	JsonNode *tmp_reader;
	
	int health [6];
	
	json_reader_read_member(reader, "spieler");
	tmp_node = json_reader_get_value(reader);
	tmp_reader = json_reader_new(tmp_node);
	int *i;
	for(i = 0; i <= 5; i++){
		json_reader_read_member(tmp_reader, i);
		json_reader_read_member(tmp_reader, "health");
		health[i] = json_reader_get_value(tmp_reader);
		json_reader_end_member(tmp_reader);
		json_reader_end_member(tmp_reader);
	}
	
	g_object_unref (parser);
}