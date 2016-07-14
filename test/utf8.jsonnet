{
	params: {
		"person" : {"name": "姓名"} ,
		"content": "我是汉字",
		"d": "123456",
		"e.portal": "www.cloudwise.com"
	},
	content: {
		"n" : $.params.person.name,
		"c" : $.params.content,
		"e" : $.params["e.portal"]
	}
}