#include "stdafx.h"

//	подключаем библиотеки
#include "../demay/scope_guard.hpp"
#include "../demay/format.hpp"

//	подключаем заголовочный файл
//#include "../demay/http_form_args.hpp"

//	подключаем заголовочный файл
//	для доступа к данным:
//		в 'mod_child_init' подключаемся к БД  
//		в 'mod_child_exit' отключаемся от БД
#include "db.hpp"
//	имя файла БД и пользователь БД с 
//	паролем БД берется из apache.conf



//	подключаем заголовочный файл
//	контроллера интерфейса пользователя
//#include "controller.hpp"
//	объекту контроллеру интерфейса передаем объект класса БД




//	подключаем заголовочный файл
//	контроллера интерфейса пользователя
#include "ui.hpp"


#ifdef _DEBUG
#include "../demay/file.hpp"
#include "../demay/format.hpp"
#endif


#define MOD_NAME "mod_gip.so"




extern "C" module MODULE_VAR_EXPORT mod_pro;

char* config_db_file = 0;
char* config_db_user = 0;
char* config_db_pass = 0;
// следующие две переменные используется в 'mod_handler'
char* config_mod_url = 0;
int   config_max_len = 65535;
// объект для доступа в БД
DB_Handle db_connection;


/*
 * Command handler for a TAKE1 directive.  TAKE1 commands must always have
 * exactly one arguments.
 *
 * static const char *handle_TAKE1(cmd_parms *cmd, void *mconfig, char *arg);
 *
 */
char const* mod_cmd_dbfile(cmd_parms* cmd, void** cfg, char* arg) {
	#ifdef _DEBUG
	function func(MOD_NAME ":" __FUNCTION__);
	#endif
	if( 0==config_mod_url && 0!=cmd->path ) config_mod_url = ::ap_pstrdup(cmd->pool, cmd->path);
	if (!(*arg)) return "'db_file' string cannot be empty";
	config_db_file = ::ap_pstrdup(cmd->pool, arg);
		//server_rec* s = cmd->server;
		//void** config = (void**)ap_get_module_config(s->module_config, &mod_pro);
		//DPRINTF("%s(config_db_file = '%s')\r\n",__FUNCTION__, arg);
	return NULL;
}

char const* mod_cmd_dbpass(cmd_parms* cmd, void** cfg, char* arg) {
	#ifdef _DEBUG
	function func(MOD_NAME ":" __FUNCTION__);
	#endif
	if( 0==config_mod_url && cmd->path ) config_mod_url = ::ap_pstrdup(cmd->pool, cmd->path);
	if (!(*arg)) return "'db_pass' string cannot be empty";
	config_db_pass = ::ap_pstrdup(cmd->pool, arg);
		//size_t dbname_len = ::strlen(arg);
		//if( config_db_file ) ap_pfree(cmd->pool, config_db_file);
		//config_db_file = (char*)ap_palloc(cmd->pool, dbname_len);
	return NULL;
}

char const* mod_cmd_dbuser(cmd_parms* cmd, void** cfg, char* arg) {
	#ifdef _DEBUG
	function func(MOD_NAME ":" __FUNCTION__);
	#endif
	if( 0==config_mod_url && cmd->path ) config_mod_url = ::ap_pstrdup(cmd->pool, cmd->path);
	if (!(*arg)) return "'db_user' string cannot be empty";
	config_db_user = ::ap_pstrdup(cmd->pool, arg);
	return NULL;
}


/*!
 *	This function is called during server initialisation when an heavy-weight
 *	process (such as a child) is being initialised.  As with the
 *	module-initialisation function, any information that needs to be recorded
 *	must be in static cells, since there's no configuration record.
 *\return
 *	There is no return value.
 *\note
 *	All our process-initialiser does is add its trace to the log.
 */
void mod_child_init(server_rec* s, pool* p) {
	#ifdef _DEBUG
	function func(MOD_NAME ":" __FUNCTION__);
	#endif
	#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF /*| _CRTDBG_CHECK_ALWAYS_DF*/ | _CRTDBG_LEAK_CHECK_DF /*| _CRTDBG_DELAY_FREE_MEM_DF*/);
	#endif
	try {
		db_connection.connect(config_db_file, config_db_user, config_db_pass);
		//if( config_db_file ) ap_pfree(p, config_db_file);
		//void** config = (void**)ap_get_module_config(s->module_config, &mod_pro);
		//mod_atm_rec* atm_rec_ptr = (mod_atm_rec*)*config;
//		DPRINTF("%s - isc_attach_database('%s')\n", __FUNCTION__, config_db_file);
		//char *sname = s->server_hostname;
		//s->module_config
		/*
		 * Set up any module cells that ought to be initialised.
		 *
		ViewFactory.Register("sales_input.html", ViewSalesInputCreator);
		ViewFactory.Register("packing_order.html", PackingOrderCreator);
		ViewFactory.Register("stocking_order.html", StockingOrderCreator);
		ViewFactory.Register("purchase_order.html", PurchaseOrderCreator);
		ViewFactory.Register("worker_pay.html", WorkerPayCreator);
		ViewFactory.Register("result_month.html", ResultMonthCreator);
		ViewFactory.Register("product_record.html", ProductRecordCreator);
		ViewFactory.Register("packing", PackingOrderNewCreator);
		ViewFactory.Register("stocking", StockingOrderNewCreator);
		*/
	} catch(std::exception const& e) {
		::ap_log_error(__FILE__, __LINE__, APLOG_ERR|APLOG_NOERRNO, s, MOD_NAME"-> exception in '"__FUNCTION__"'. %s", e.what());
	}
}

/*!
 *	This function is called when an heavy-weight process (such as a child) is
 *	being run down or destroyed.  As with the child-initialisation function,
 *	any information that needs to be recorded must be in static cells, since
 *	there's no configuration record.
 *\return
 *	There is no return value.
 *\note
 *	All our process-death routine does is add its trace to the log.
 */
void mod_child_exit(server_rec* s, pool* p) {
	#ifdef _DEBUG
	function func(MOD_NAME ":" __FUNCTION__);
	#endif
	try {
		db_connection.disconnect();
	} catch(std::exception const& e) {
		::ap_log_error(__FILE__, __LINE__, APLOG_ERR|APLOG_NOERRNO, s, MOD_NAME"-> exception in '"__FUNCTION__"'. %s", e.what());
	}
}

/*!
 * This function gets called to create a per-server configuration
 * record.  It will always be called for the "default" server.
 *\return
 *	Указатель на созданную структуру конфигурации модуля (module-specific structure).
 */
void* mod_create_server_config(pool* p, server_rec* s) {
	#ifdef _DEBUG
	function func(MOD_NAME ":" __FUNCTION__);
	#endif
	//excfg *cfg;
	//char *sname = s->server_hostname;

	/*
	 * As with the example_create_dir_config() reoutine, we allocate and fill
	 * in an empty record.
	 */
	//mod_cfg_rec* cfg = 0;//(mod_cfg_rec*)ap_pcalloc( p, sizeof(mod_cfg_rec) );
	//cfg->local = 0;
	//cfg->congenital = 0;
	//cfg->cmode = CONFIG_MODE_SERVER;
	/*
	 * Note that we were called in the trace list.
	 
	sname = (sname != NULL) ? sname : "";
	cfg->loc = ap_pstrcat(p, "SVR(", sname, ")", NULL);
	trace_add(s, NULL, cfg, "example_create_server_config()");*/
	void** cfg = (void**)ap_pcalloc( p, sizeof(void*) ); *cfg = 0;
//	DPRINTF("%s ... return cfg_ptr = 0x%08x s->path = %s, s->defn_name = %s, s->defn_line_number = %i\r\n",__FUNCTION__,cfg,s->path,s->defn_name,s->defn_line_number);
	//return (void*) cfg;
	return cfg;
}

static void mod_html_end(request_rec* r) {
	::ap_rputs("</body>\r\n</html>", r);
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/* Now we declare our content handlers, which are invoked when the server   */
/* encounters a document which our module is supposed to have a chance to   */
/* see.  (See mod_mime's SetHandler and AddHandler directives, and the      */
/* mod_info and mod_status examples, for more details.)                     */
/*                                                                          */
/* Since content handlers are dumping data directly into the connexion      */
/* (using the r*() routines, such as rputs() and rprintf()) without         */
/* intervention by other parts of the server, they need to make             */
/* sure any accumulated HTTP headers are sent first.  This is done by       */
/* calling send_http_header().  Otherwise, no header will be sent at all,   */
/* and the output sent to the client will actually be HTTP-uncompliant.     */
/*--------------------------------------------------------------------------*/
/* 
 * Sample content handler.  All this does is display the call list that has
 * been built up so far.
 *
 * The return value instructs the caller concerning what happened and what to
 * do next:
 *  OK ("we did our thing")
 *  DECLINED ("this isn't something with which we want to get involved")
 *  HTTP_mumble ("an error status should be reported")
 */
extern "C" 
int mod_handler(request_rec* r) {
	::OutputDebugString("\n\n--------------------------------------------------------------------------------\n");
	#ifdef _DEBUG
	function func(MOD_NAME ":" __FUNCTION__);
	#endif

	/*
	 * We're about to start sending content, so we need to force the HTTP
	 * headers to be sent at this point.  Otherwise, no headers will be sent
	 * at all.  We can set any we like first, of course.  **NOTE** Here's
	 * where you set the "Content-type" header, and you do so by putting it in
	 * r->content_type, *not* r->headers_out("Content-type").  If you don't
	 * set it, it will be filled in with the server's default type (typically
	 * "text/plain").  You *must* also ensure that r->content_type is lower
	 * case.
	 *
	 * We also need to start a timer so the server can know if the connexion
	 * is broken.
	 */ 
	r->content_type = "text/html";
	r->no_cache = r->no_local_copy = 1;
	::ap_send_http_header(r);
	/* 
	 *	если требуется отправить только заголовок (HEAD запрос), то ничего не делаем
	 */
	if( !r->header_only ) {
		::ap_soft_timeout(MOD_NAME, r);
		ScopeGuard sg_ap_kill_timeout(MakeGuard(&::ap_kill_timeout, r));

		std::string html_header(
			"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\r\n"
			"<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n"
			"<head>\r\n"
			"\t<title>mod_pro</title>\r\n"
			// мета-тег X-UA-Compatible должен быть помещен в HEAD страницы самым первым по счету, 
			// если его поставить после любого другого мета-тега, например, после иконки или заголовка страницы, 
			// то он будет просто проигнорирован. Не забывайте про эту особенность, когда будете верстать свой сайт. 
			// Как вариант, мета-тег X-UA-Compatible можно использовать для проверки отображения сайта под разными 
			// версиями IE, не устанавливая сами браузеры, а имея только один установленный IE8.
			"\t<meta http-equiv=\"X-UA-Compatible\" content=\"IE=8\" />\r\n"
			"\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1251\" />\r\n"
			"\t<meta http-equiv=\"Expires\" content=\"immediately\"/ />\r\n"
			"\t<meta name=\"robots\" content=\"noindex,nofollow\" />\r\n"
			"\t<meta name=\"document-state\" content=\"dynamic\" />\r\n"
			"\t<meta name=\"Pragma\" content=\"no-cache\" />\r\n"
			"\t<link rel=\"stylesheet\" media=\"all\" type=\"text/css\" href=\"");
		//! в элементе <link ...> заголовка настройка таблицы стилей использует config_mod_url
		html_header.append(config_mod_url); 
		html_header.append(".css\" />\r\n"
			//"\t<link rel=\"stylesheet\" type=\"text/css\" media=\"screen\" href=\"//www.ibm.com/common/v14/screen.css\"/>
			//"\t<link rel=\"stylesheet\" type=\"text/css\" media=\"print\" href=\"//www.ibm.com/common/v14/print.css\"/>
			"\t<style>\r\n"
			"\t.cell_btn {\r\n"
			"\t	border-width: 0px;\r\n"
			"\t	background-color: #FFFFFF;\r\n"
			"\t	font-size: 11pt;\r\n"
			"\t	font-family: Verdana, Arial, Helvetica;\r\n"
			"\t	cursor: pointer;\r\n"
			"\t	cursor: hand;\r\n"
			"\t}\r\n"
			"\t.tbl_cell {\r\n"
  			"\t	display: table-cell;\r\n"
			"\t	font-size: 12pt;\r\n"
			"\t	font-family: Arial;\r\n"
	//		"\t	width: 30px;\r\n"
	//		"\t	height: 1px;\r\n"
			"\t	border: 2px solid #777777;\r\n"
	//		"\tpadding: 1em;\r\n"
			"\t}\r\n"
			"\t</style>\r\n"
	//"\t<script type=\"text/javascript\">\r\n"
	//"\t\tfunction dataField(f){\r\n"
	//"\t\talert(\"Вы ввели: \" + f.value);\r\n"
	//"\t\t}\r\n"
	//"\t</script>\r\n"
			"</head>\r\n"
			"<body>\r\n");
		::ap_rputs(html_header.c_str(), r); 
		ScopeGuard sg_mod_html_end(MakeGuard(&::mod_html_end, r));
	
		/*
		 * Locate our directory configuration record for the current request.
		 */
		//excfg* conf_struct = (excfg*)ap_get_module_config(r->per_dir_config, &mod_pro);
		/*
		 * Now send our actual output.  Since we tagged this as being
		 * "text/html", we need to embed any HTML.
		 */
		try {
			if( M_POST==r->method_number ) {
				//::ap_hard_timeout(MOD_NAME, r);
				//ScopeGuard sg_ap_kill_timeout = MakeGuard(&::ap_kill_timeout, r);

				//
				// настраиваем структуры Apache и получаем клиентские http-данные
				//
				if( ::ap_setup_client_block(r, REQUEST_CHUNKED_ERROR) )
					throw std::runtime_error(__FUNCTION__":'::ap_setup_client_block' failed");
				long const cln_http_data_size = r->remaining;
				if( cln_http_data_size<=0 ) throw std::runtime_error(__FUNCTION__": invalid content length <=0");
				if( cln_http_data_size>=config_max_len ) throw std::runtime_error(__FUNCTION__": content length too large (config:post_max_sz).");
				char* const cln_http_data_ptr = (char* const)::malloc(cln_http_data_size);
				if( 0==cln_http_data_ptr ) throw std::runtime_error(__FUNCTION__":'::malloc' for 'client_http_data_block' failed");
				ScopeGuard sg_cln_http_data_free(MakeGuard(&::free, cln_http_data_ptr));
				char* const cln_http_data_end = cln_http_data_ptr + cln_http_data_size;
				if( ::ap_should_client_block(r)) {
					long const cln_http_data_len = ::ap_get_client_block(r, cln_http_data_ptr, cln_http_data_size);
					if( cln_http_data_len!=cln_http_data_size ) {
						std::string err_str; 
						::format(err_str, 
								__FUNCTION__": '::ap_get_client_block' returned %1 bytes, content length %2 bytes\r\b", 
								cln_http_data_len, cln_http_data_size
								);
						#ifdef _DEBUG
						{::Sleep(10); FILETIME ft; ::GetSystemTimeAsFileTime(&ft);
						std::string file_name_r; ::format(file_name_r, "%1%2-RECV.txt", (void*)ft.dwHighDateTime, (void*)ft.dwLowDateTime);
						File<FileOpening::CreateAlways, FileAccess::ReadWrite, FileShare::ShareReadWriteDelete> file_r(file_name_r.c_str());
						file_r.write(cln_http_data_ptr, cln_http_data_size);}
						#endif
						::OutputDebugString(err_str.c_str());
						//throw std::runtime_error(err_str);
					}
				} else throw std::runtime_error(__FUNCTION__": '::ap_should_client_block' failed");
				//-::ap_reset_timeout(r);
				//-::ap_kill_timeout(r);

				// получаем строку являющуюся разделителем http-аргументов вида: 'имя'\r\n'значение'
				char const* const delimit_ptr = (char*)::ap_table_get(r->headers_in, "Content-Type");
				if( 0==delimit_ptr ) throw std::runtime_error(__FUNCTION__": '::ap_table_get' failed, for 'Content-Type' returned null");
				char const* const delimit_end = delimit_ptr + ::strlen(delimit_ptr);

				HttpArgs http_args(cln_http_data_ptr, cln_http_data_end, delimit_ptr, delimit_end);
				UI_Control cont;
				std::string html_output;
				cont.ui_handler(html_output, http_args, db_connection);
				::ap_rputs(html_output.c_str(), r);

				#ifdef _DEBUG
				{::Sleep(10); FILETIME ft; ::GetSystemTimeAsFileTime(&ft);
				std::string file_name_r; ::format(file_name_r, "%1%2-RECV.txt", (void*)ft.dwHighDateTime, (void*)ft.dwLowDateTime);
				std::string file_name_s; ::format(file_name_s, "%1%2-SEND.txt", (void*)ft.dwHighDateTime, (void*)ft.dwLowDateTime);
				File<FileOpening::CreateAlways, FileAccess::ReadWrite, FileShare::ShareReadWriteDelete> file_r(file_name_r.c_str());
				File<FileOpening::CreateAlways, FileAccess::ReadWrite, FileShare::ShareReadWriteDelete> file_s(file_name_s.c_str());
				file_s.write(html_output.c_str(), html_output.size()); 
				file_r.write(cln_http_data_ptr, cln_http_data_size);}
				#endif
			} else if( M_GET==r->method_number ) {

				// выдать страницу для ввода имени пользователя и пароля
				::ap_rputs(
					"\t<table cellspacing=\"0\" cellpadding=\"1\" align=\"center\" valign=\"center\"><tr><td>\r\n"
					"\t<span class=\"rbfullbox\" style='text-align:left;'><b class=\"rbtbtop\"><b class=\"rbtbb1\"></b><b class=\"rbtbb2\"></b><b class=\"rbtbb3\"></b><b class=\"rbtbb4\"></b></b><span class=\"rbtbboxcontent\">\r\n"
					"\t<h3 class=\"rbtbboxtitle maintitleborderd\">login</h3>\r\n"
					"\t<div class=\"x2textcontent\">\r\n"
					"\t<div id=\"27779260342010226_Automatic_Headlines_1\" style=\"display: inline-table;\">\r\n"
					"\t<form method=\"post\" enctype=\"multipart/form-data\">\r\n"
					"\t\t<table cellspacing=\"0\" cellpadding=\"1\">\r\n"
					"\t\t<tr><td>Пользователь:</td><td><input type=\"text\" name=\"user\" maxlength=\"32\" value=\"\"></td></tr>\r\n"
					"\t\t<tr><td>Пароль:</td><td><input type=\"password\" name=\"pass\" maxlength=\"32\" value=\"\"></td></tr>\r\n"
					"\t\t<tr><td></td><td><input type=\"submit\" name=\"btn\" value=\">\" title=\"Авторизоваться\"/></td></tr>\r\n"
					"\t\t</table>\r\n"
					"\t</form>\r\n"
					"\t</div></div>\r\n"
					"</span><b class=\"rbtbbottom\"><b class=\"rbtbb8\"></b><b class=\"rbtbb7\"></b><b class=\"rbtbb6\"></b><b class=\"rbtbb5\"></b></b></span>\r\n"
					"\t<div style=\"height:8px\"></div>\r\n"
					"\t</tr></table>\r\n"
					,r);
				/*
				 * КОД НИЖЕ БЫЛ В МОДУЛЕ http://www.modsecurity.org/download/, НЕ ВХОДЯЩЕГО В ПОСТАВКУ Apache 
				 * 
				 * here we alter Apache internal structures to point those pointers to our buffer
				 * and to reset counters so that Apache will think that the payload was not read at all
				 *
				 r->connection->client->inptr = (unsigned char *)buffer;
				 r->connection->client->incnt = size + 1;
				 r->remaining = size + 1;
				 r->read_length = 0;*/
			}
		} catch(const std::exception& e) {
			//API_EXPORT(void) ap_send_error_response(request_rec *r, int recursive_error);
			::ap_log_rerror(__FILE__, __LINE__, APLOG_ERR|APLOG_NOERRNO, r, MOD_NAME"-> exception in '"__FUNCTION__"'. %s", e.what());
			::ap_rputs("<b>"MOD_NAME"-> exception in '"__FUNCTION__"':</b><pre>\r\n", r);
			::ap_rputs(e.what(), r); ::ap_rputs("</pre>\r\n<a href=\"", r); ap_rputs(config_mod_url, r);
			::ap_rputs("/\">&nbsp;На главную страницу...&nbsp;</a>\r\n", r);
		}
		// здесь ScopeGuard делает за нас '::ap_rputs("</body>\r\n</html>\r\n", r);'
		// чтобы отменить ранее поставленный таймаут
		/*
		 * We're all done, so cancel the timeout we set.  Since this is probably
		 * the end of the request we *could* assume this would be done during
		 * post-processing - but it's possible that another handler might be
		 * called and inherit our outstanding timer.  Not good; to each its own.
		 */
		// здесь ScopeGuard отменит поставленный ранее таймаут делая за нас '::ap_kill_timeout(r);'
	}
	/*
	 * We did what we wanted to do, so tell the rest of the server we
	 * succeeded.
	 */
	return OK; 
}

/*
void* make_config_log_state( pool *p, server_rec *s) {
	config_log_state *cls = (config_log_state *)palloc (p, sizeof (config_log_state));

	cls->fname = NULL;
	cls->format = NULL;
	cls->log_fd = -1;

	return (void *)cls;
}
*/

//typedef const char *(*func) ();
static const command_rec access_cmds[] = {
	// ACCESS_CONF => *.conf inside <Directory> or <confHomeDir>
	{"db_file", (const char *(*)())mod_cmd_dbfile, NULL, ACCESS_CONF, TAKE1, "Database file name"},
	{"db_user", (const char *(*)())mod_cmd_dbuser, NULL, ACCESS_CONF, TAKE1, "User for connect to database"},
	{"db_pass", (const char *(*)())mod_cmd_dbpass, NULL, ACCESS_CONF, TAKE1, "Password for connect to database"},
	//{ "MaxClientDataSize", set_error_document, NULL, OR_FILEINFO, RAW_ARGS,
	//  "Change responses for HTTP errors" },
	//{"MaxClientDataSize", mod_cmd_atm_iterator, NULL, OR_AUTHCFG, ITERATE,
	// "a space-separated list of ATM numbers"},
	//{ "Vendor", mod_vendor_iter, NULL, OR_AUTHCFG, TAKE2, "name and file name Vendors" },
	//{ "Provider", mod_provider_iter, NULL, OR_AUTHCFG, TAKE2, "name and file name Providers" },
	//{ "ATM", set_error_document, NULL, OR_FILEINFO, RAW_ARGS,
	//  "Change responses for HTTP errors" },
	//{"order", order, NULL, OR_LIMIT, TAKE1,
	// "'allow,deny', 'deny,allow', or 'mutual-failure'"},
	//{"allow", allow_cmd, &its_an_allow, OR_LIMIT, ITERATE2,
	// "'from' followed by hostnames or IP-address wildcards"},
	//{"deny", allow_cmd, NULL, OR_LIMIT, ITERATE2,
	// "'from' followed by hostnames or IP-address wildcards"},
	{0}
};

static const handler_rec mod_handler_rec[] = {
	//{ STATUS_MAGIC_TYPE, mod_handler },
	{ "mod_pro_handler", mod_handler },
	{ 0 }
};

module MODULE_VAR_EXPORT mod_pro = {
	STANDARD_MODULE_STUFF,
	NULL,                  // initializer
	NULL,                  // dir config creater (create_access_dir_config)
	NULL,                  // dir merger --- default is to override
	NULL,                  // server config (mod_create_server_config)
	NULL,                  // merge server config
	access_cmds,
	mod_handler_rec,       // handlers
	NULL,                  // filename translation
	NULL,                  // check_user_id
	NULL,                  // check auth
	0,//check_dir_access,		// check access
	NULL,                  // type_checker
	NULL,                  // fixups
	NULL,                  // logger
	NULL,                  // header parser
	mod_child_init,        // child_init
	mod_child_exit,        // child_exit
	NULL                   // post read-request
};



/*
int sqlite3_run();

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	return sqlite3_run();

}
*/