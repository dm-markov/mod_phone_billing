

#include "ui.hpp"

#include "../demay/file.hpp"
#include "../demay/format.hpp"
#include "../demay/scope_guard.hpp"
//#include "../demay/auto_buf.hpp"

//	подключаем заголовочный файл
//	для доступа к данным в базе данных:
//		подключение в 'mod_child_init' 
//		отключение в 'mod_child_exit'
#include "db.hpp"
//	имя файла БД и пользователь БД с 
//	с паролем БД берется из apache.conf


#include "../sqlite-3.6.22/src/sqlite.h.in"

extern sqlite3* sqlite3_handle_global;
	
void UI_View::handler_not_exist(std::string& html_output, HttpArgs const& http_args, char event_chr) {
	//std::string html_output;
	::format(html_output, __FUNCTION__"-> in UI_View_%1 handler not found for event '%2' ", http_args("view"), event_chr);
	#ifdef _DEBUG
	::OutputDebugString("\t\tthrow std::exception -> "); ::OutputDebugString(html_output.c_str());
	#endif
	//throw std::exception(html_output.c_str());
}

char const* UI_Control::http_form_args_insert_pair(char const* name_ptr, char const* name_end, char const* value_ptr, char const* value_end) {
	std::string const name_str(name_ptr, name_end);
	std::string const value_str(value_ptr, value_end);
	http_form_args_pool_type::iterator args_iter(args_pool_.find(name_str));
	if( args_pool_.end()==args_iter ) {
		args_pool_.insert(std::make_pair(name_str, value_str));
		//args_iter->second
	} else {
		//#ifdef _DEBUG
		//{ std::string const value_str(value_ptr, value_end); std::string deb_out; ::format(deb_out, __FUNCTION__"-> name '%1'=='%2', new value '%3'\r\n", name_str, args_iter->second, value_str ); ::OutputDebugString(deb_out.c_str()); }
		//#endif
		args_iter->second.assign(value_str);
	}

	return 0;
}

/*!
 *	0) Разобрать blob-строку переменных от http-сервера.<br/>
 *	1) Исходя из значения http-переменной view, найти соответствующий объект UI_View и вызвать его метод handler.<br/>
 *	2) Если http-переменная btn не содержит '>', присвоить event_chr '>', т.к. логика перехода в другое состояние реализована в методе handler объекта.<br/>
 *	3) Вызвать handler найденного объекта.
 */
void UI_Control::ui_handler(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	// ЕСЛИ Заработает UI_Control как потомок HttpFormArgs<> то раскомментировать сторку ниже 
	// UI_View* view_ptr = view_arg2ptr();
	std::string const view_str = http_args("view");
	UI_View* view_ptr = view_str2ptr(view_str);

	/// todo: ТРЕБУЕТСЯ_ДОРАБОТКА: если btn не несет информации что нажата кнопка, заложена логика прямого перехода в viewX
	//char btn_chr = '>';	/// todo: чего тут непонятно
	std::string const btn_str = http_args("btn");
	//if( !btn_str.empty() ) btn_chr = btn_str.at(0);
	char const btn_chr = !btn_str.empty()?btn_str.at(0):'>';
	/// todo: ТРЕБУЕТСЯ_ДОРАБОТКА: если btn не несет информации что нажата кнопка, заложена логика прямого перехода в viewX
	//char btn_chr = '>';	/// todo: чего тут непонятно

	#ifdef _DEBUG
	{std::string deb_str; ::format(deb_str, "    "__FUNCTION__"-> view_id=%1, view_ptr=0x%2, btn_chr='%3'\r\n", http_args("view"), (void*)view_ptr, btn_chr); ::OutputDebugString(deb_str.c_str());}
	#endif
	switch(btn_chr) {
		case '0':	view_ptr->ev_0(html_output, http_args, db_handle);	break;
		case '1':	view_ptr->ev_1(html_output, http_args, db_handle);	break;
		case '2':	view_ptr->ev_2(html_output, http_args, db_handle);	break;
		case '3':	view_ptr->ev_3(html_output, http_args, db_handle);	break;
		case '4':	view_ptr->ev_4(html_output, http_args, db_handle);	break;
		case '5':	view_ptr->ev_5(html_output, http_args, db_handle);	break;
		case '6':	view_ptr->ev_6(html_output, http_args, db_handle);	break;
		case '7':	view_ptr->ev_7(html_output, http_args, db_handle);	break;
		case '8':	view_ptr->ev_8(html_output, http_args, db_handle);	break;
		case '9':	view_ptr->ev_9(html_output, http_args, db_handle);	break;
		case '<':	view_ptr->ev_prev(html_output, http_args, db_handle);	break;
		case '>':	view_ptr->ev_next(html_output, http_args, db_handle);	break;
		case '+':	view_ptr->ev_plus(html_output, http_args, db_handle);	break;
		case '-':	view_ptr->ev_minus(html_output, http_args, db_handle);	break;
		case '^':	view_ptr->ev_up(html_output, http_args, db_handle); 	break;
		case 'v':	view_ptr->ev_down(html_output, http_args, db_handle);	break;
		case 'a':	view_ptr->ev_char_a(html_output, http_args, db_handle);	break;
		//todo: остальный буквы латинского алфавита ...
		case 'z':	view_ptr->ev_char_z(html_output, http_args, db_handle);	break;
		default:	view_ptr->handler_not_exist(html_output, http_args, btn_chr);	break;
	}
}


/*!
 *	Конструктор (фабрика объектов UI_View)
 *	1) Создать пул объектов UI_View, размещаемых в std::map
 *	х) Создание пула имен и значений http- переменных (вроде как по todo выноситься из класса) 
 */
UI_Control::UI_Control() {
	// explicit UI_View(UI_Control* ui_control_ptr
	UI_View* view0_ptr = new UI_View0();
	view_pool_.insert(std::pair<int, UI_View*>(0, view0_ptr));
	view_pool_.insert(std::pair<int, UI_View*>(1, new UI_View1()));
	view_pool_.insert(std::pair<int, UI_View*>(11, new UI_View11()));
	view_pool_.insert(std::pair<int, UI_View*>(12, new UI_View12()));
	view_pool_.insert(std::pair<int, UI_View*>(111, new UI_View111()));
	view_pool_.insert(std::pair<int, UI_View*>(123, new UI_View123()));
}

UI_Control::~UI_Control() {
	std::map<int const, UI_View* const>::const_iterator view_pool_iter_0(view_pool_.find(0));
	if( view_pool_.end()!=view_pool_iter_0 ) delete view_pool_iter_0->second;

	std::map<int const, UI_View* const>::const_iterator view_pool_iter_1(view_pool_.find(1));
	if( view_pool_.end()!=view_pool_iter_1 ) delete view_pool_iter_1->second;

	std::map<int const, UI_View* const>::const_iterator view_pool_iter_11(view_pool_.find(11));
	if( view_pool_.end()!=view_pool_iter_11 ) delete view_pool_iter_11->second;

	std::map<int const, UI_View* const>::const_iterator view_pool_iter_12(view_pool_.find(12));
	if( view_pool_.end()!=view_pool_iter_12 ) delete view_pool_iter_12->second;

	std::map<int const, UI_View* const>::const_iterator view_pool_iter_111(view_pool_.find(111));
	if( view_pool_.end()!=view_pool_iter_111 ) delete view_pool_iter_111->second;

	std::map<int const, UI_View* const>::const_iterator view_pool_iter_123(view_pool_.find(123));
	if( view_pool_.end()!=view_pool_iter_123 ) delete view_pool_iter_123->second;
}


void UI_Control::sql_insert_prod_to_spec(std::string const& spec_str, std::string const& prod_str, std::string const& name_str, int amount) {
	#ifdef _DEBUG
	function func("        "__FUNCTION__);
	#endif
	
	static int x = 399;
	std::string indx_str;
	::format(indx_str, "%1", ++x);


	// -- BEGIN SQL CODE ---------------------------
	std::string sql_statement_utf8enc;
	::format(sql_statement_utf8enc, 
			"insert into SPECS values('%1', '%2', '%3', '%4', %5, '%6', %7, %8, '%9', 0)", 
			spec_str,   // 1) SPEC_ID        - идентификатор спецификации
			indx_str,   // 2) SPEC_INDX      - упорядочивающий номер записи
			prod_str,   // 3) SPEC_PROD_ART  - ссылочный (PRODUCTS) артикул единицы оборудования
			name_str,   // 4) SPEC_PROD_NAME - наименование единицы оборудования для пользователя
			amount,     // 5) SPEC_PROD_AMT  - количество единиц оборудования
			"",         // 6) SPEC_PROD_UNIT - единица измерения оборудования
			0,          // 7) SPEC_PRICE_ID  - идентификатор поставщика
			0,          // 8) SPEC_PRICE_USR - цена EndUser оборудования
			""         // 9) SPEC_PRICE_VAL - валюта цены прайса
//			0           // 10) SPEC_PRICE_OUR - our cost наша цена
	);

	#ifdef _DEBUG
	{std::string deb_out; ::format(deb_out, "    %1 \"%2\"\r\n", __FUNCTION__, sql_statement_utf8enc); ::OutputDebugString(deb_out.c_str());}
	#endif

	sqlite3_stmt* stmt_handle(0);
	int sqlt_code = ::sqlite3_prepare_v2(
			::sqlite3_handle_global,         // Database handle
			sql_statement_utf8enc.c_str(),   // SQL UI_Viewment, UTF-8 encoded
			sql_statement_utf8enc.length(),  // Maximum length of zSql in bytes.
			&stmt_handle,                    // OUT: UI_Viewment handle
			0                                // OUT: Pointer to unused portion of zSql
			);
	if( sqlt_code ) throw std::exception("'::sqlite3_prepare_v2' failed in "__FUNCTION__);

	while( 100==(sqlt_code = ::sqlite3_step(stmt_handle)) ) {
		#ifdef _DEBUG
		{std::string deb_out; ::format(deb_out, "%1 \"%2\"\r\n", __FUNCTION__, "100==(sqlt_code = ::sqlite3_step(stmt_handle))"); ::OutputDebugString(deb_out.c_str());}
		#endif
	}

	#ifdef _DEBUG
	{std::string deb_out; ::format(deb_out, "%1 %2%3\r\n", __FUNCTION__, "sqlt_code = ::sqlite3_step == ",sqlt_code); ::OutputDebugString(deb_out.c_str());}
	#endif

	sqlt_code = ::sqlite3_finalize(stmt_handle);

	#ifdef _DEBUG
	{std::string deb_out; ::format(deb_out, "%1 %2%3\r\n", __FUNCTION__, "sqlt_code = ::sqlite3_finalize == ",sqlt_code); ::OutputDebugString(deb_out.c_str());}
	#endif
	/*#ifdef _DEBUG
	if( sqlt_code ) {
		std::string err_msg; 
		::format(err_msg, 
				"'::sqlite3_finalize' failed in "__FUNCTION__" с кодом <b>%1</b><br/>\r\n",
				sqlt_code);
		throw std::exception(err_msg.c_str());
	}
	#endif*/
	// -- END SQL CODE ---------------------------

}

/*
	Вывести содержимое заказа для ид.заказа в calc_str
*/
void UI_Control::sql_select_prods_for_spec(std::string const& spec_str) {
	//todo: обработку header
	//todo: подсчет итогов
	//todo: единица измерений
	//todo: вывод валюты
	//#ifdef _DEBUG
	//function func("       "__FUNCTION__);
	//#endif

	html_output_.append(
			"\t\t<table cellspacing=\"0\" cellpadding=\"3\"><tr>\r\n"
			"\t\t\t<td class=\"c0\" bgcolor=#CCCCCC><font color=#FFFFFF><b>П/п</b></font></td>\r\n"
			"\t\t\t<td class=\"c1\" bgcolor=#CCCCCC><font color=#FFFFFF><b>Артикул</b></font></td>\r\n"
			"\t\t\t<td class=\"c1\" bgcolor=#CCCCCC><font color=#FFFFFF><b>Наименование</b></font></td>\r\n"
			"\t\t\t<td class=\"c1\" bgcolor=#CCCCCC><font color=#FFFFFF><b>Кол-во</b></font></td>\r\n"
			"\t\t\t<td class=\"c1\" bgcolor=#CCCCCC><font color=#FFFFFF><b>Цена</b></font></td>\r\n"
			);

	// -- BEGIN SQL CODE ---------------------------
	std::string sql_statement_utf8enc;
	::format(sql_statement_utf8enc, 
			//"select SPEC_INDX, SPEC_PROD_ART, SPEC_PROD_NAME, SPEC_PROD_AMT, (select min(PRICE_END_USER) from PRICES where PROD_ART=PRICE_PROD_ART), SPEC_PRICE_VAL from SPECS, PRODUCTS where PROD_ART=SPEC_PROD_ART and SPEC_ID='%1'",
			//"select SPEC_INDX, SPEC_PROD_ART, SPEC_PROD_NAME, SPEC_PROD_AMT, SPEC_PROD_UNIT, SPEC_PRICE_USR, SPEC_PRICE_VAL from SPECS, PRODUCTS where PROD_ART=SPEC_PROD_ART and SPEC_ID='%1'",
			"select SPEC_INDX, SPEC_PROD_ART, SPEC_PROD_NAME, SPEC_PROD_AMT, SPEC_PROD_UNIT, SPEC_PRICE_USR, SPEC_PRICE_VAL from SPECS where SPEC_ID='%1'",
	        spec_str);
	#ifdef _DEBUG
	{std::string deb_out; ::format(deb_out, "\n    %1;\n\n", sql_statement_utf8enc); ::OutputDebugString(deb_out.c_str());}
	#endif

	sqlite3_stmt* stmt_handle(0);
	int sqlt_code = ::sqlite3_prepare_v2(
			::sqlite3_handle_global,         // Database handle
			sql_statement_utf8enc.c_str(),   // SQL UI_Viewment, UTF-8 encoded
			sql_statement_utf8enc.length(),  // Maximum length of zSql in bytes
			&stmt_handle,                    // OUT: UI_Viewment handle
			0                                // OUT: Pointer to unused portion of zSql
			);
	if( sqlt_code ) throw std::exception("'::sqlite3_prepare_v2' failed in "__FUNCTION__);

	while( 100==(sqlt_code=::sqlite3_step(stmt_handle)) ) {
		char const* const indx_ptr = ::sqlite3_column_bytes(stmt_handle, 0)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 0)):"null";
		char const* const prod_ptr = ::sqlite3_column_bytes(stmt_handle, 1)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 1)):"null";
		char const* const name_ptr = ::sqlite3_column_bytes(stmt_handle, 2)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 2)):"null";
		char const* const amount_ptr = ::sqlite3_column_bytes(stmt_handle, 3)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 3)):"null";
		char const* const prod_unit_ptr = ::sqlite3_column_bytes(stmt_handle, 4)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 4)):"null";
		char const* const price_usr_ptr = ::sqlite3_column_bytes(stmt_handle, 5)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 5)):"null";
		char const* const price_val_ptr = ::sqlite3_column_bytes(stmt_handle, 6)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 6)):"null";
		if( 1819047278!=*(long*)prod_ptr && 1819047278!=*(long*)name_ptr ) {
			#ifdef _DEBUG
			{std::string deb_out; ::format(deb_out, "    SQL_DATA(\"%1\", \"%2\", \"%3\", \"%4\")\r\n", prod_ptr, name_ptr, amount_ptr, price_usr_ptr); ::OutputDebugString(deb_out.c_str());}
			#endif
			if( "header"==std::string(prod_ptr) ) {
				::format(html_output_, 
						"\t\t\t</tr><tr>\r\n"
						"\t\t\t<td colspan=\"5\" class=\"c2\" bgcolor=#CCCCFF><font size=\"-2\"><b>%1</b></font></td>\r\n",
						name_ptr
				);
			} else {
				::format(html_output_, 
						"\t\t\t</tr><tr>\r\n"
						"\t\t\t<td class=\"c2\">%1</td>\r\n"
						"\t\t\t<td class=\"c3\">%2</td>\r\n"
						"\t\t\t<td class=\"c3\">%3</td>\r\n"
						"\t\t\t<td class=\"c3\" align=\"right\">%4&nbsp;%5</td>\r\n"
						"\t\t\t<td class=\"c3\" align=\"right\">%6&nbsp;%7</td>\r\n",
						indx_ptr,
						prod_ptr, 
						name_ptr, 
						amount_ptr, prod_unit_ptr,
						price_usr_ptr, price_val_ptr
				);
			}
		}
	}

	sqlt_code = ::sqlite3_finalize(stmt_handle);
	#ifdef _DEBUG
	if( sqlt_code ) throw std::exception("'::sqlite3_finalize' failed in "__FUNCTION__);
	#endif
	// -- END SQL CODE ---------------------------

	html_output_.append("\t\t</tr></table>\r\n");
	html_output_.append(
			"\t\t<p>\r\n"
			"\t\t<font size=\"-1\"><a href=\"mailto:ai@uetel.ru?subject=запрос%20прайс-листа%20ОрисЛайн&amp;body=Прошу%20выслать%20прайс-лист%20на%20следующее%20сетевое%20оборудование:\" class=\"link_path\">Запросить&nbsp;цены&nbsp;отсутствующих&nbsp;позиций</a></font>\r\n"
			"\t\t<p>\r\n"
	);
}



/*
 *	Получаем в <html-select>-структуру варианты (список) оборудования, которые могут быть установлены в слот slot_str
	// выполняется SQL-запрос:
	// select PROD_ART, PROD_NAME, PROD_NOTE from PRODUCTS where PROD_SLOT='%1'
 */
void UI_Control::sql_select_prods_for_slot(std::string const& slot_str) {
	//#ifdef _DEBUG
	//function func("        "__FUNCTION__);
	//#endif

	// для выбора пользователем оборудования из нескольких  
	// вариантов в переменной формируем html-тег <SELECT> 
	std::string html_tag_select;
	
	// -- BEGIN SQL CODE ---------------------------
	std::string sql_statement_utf8enc;
	::format(sql_statement_utf8enc, "select PROD_ART, PROD_NAME, PROD_NOTE from PRODUCTS where PROD_SLOT='%1'", slot_str);
	#ifdef _DEBUG
	{std::string deb_out; ::format(deb_out, "\n    %1;\n\n", sql_statement_utf8enc); ::OutputDebugString(deb_out.c_str());}
	#endif

	sqlite3_stmt* stmt_handle(0);
	int sqlt_code = ::sqlite3_prepare_v2(
		::sqlite3_handle_global,         // Database handle
		sql_statement_utf8enc.c_str(),   // SQL UI_Viewment, UTF-8 encoded
		sql_statement_utf8enc.length(),  // Maximum length of zSql in bytes.
		&stmt_handle,                    // OUT: UI_Viewment handle
		0                                // OUT: Pointer to unused portion of zSql
	);
	if( sqlt_code ) throw std::exception("'::sqlite3_prepare_v2' failed in "__FUNCTION__);

	int count = 0;
	while( 100==(sqlt_code=::sqlite3_step(stmt_handle)) ) {
		char const* const prod_art_ptr = ::sqlite3_column_bytes(stmt_handle, 0)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 0)):"null";
		char const* const prod_name_ptr = ::sqlite3_column_bytes(stmt_handle, 1)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 1)):"null";
		char const* const prod_note_ptr = ::sqlite3_column_bytes(stmt_handle, 2)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 2)):"null";
		if( 1819047278!=*(long*)prod_art_ptr && 1819047278!=*(long*)prod_name_ptr ) {
			std::string html_tag_option_title;
			// всплывающая подсказка и первый подсвеченный пункт
			char const* const option_end_tag_ptr(0==count?" selected>":">");
			if( 1819047278!=*(long*)prod_note_ptr ) ::format(html_tag_option_title, " title=\"%1\"%2", prod_note_ptr, option_end_tag_ptr);
			else html_tag_option_title.assign(option_end_tag_ptr);
			/*#ifdef _DEBUG
			char const* const style[] = {
				"style=\"font-family: 'Times New Roman'; font-size: 14pt\"; cursor: hand; cursor: pointer",
				"style=\"background-color: #ffffc0; border: 1px solid #0000ff\"; cursor: hand; cursor: pointer",
				"style=\"font-family: Georgia; font-size: 12pt\"; cursor: hand; cursor: pointer",
				"style=\"color: #f00\"; cursor: hand; cursor: pointer" };
			#endif*/
			::format(html_tag_select,
					 "\t\t\t<option value=\"%1\"%2%1 %3</option>\r\n", 
				     prod_art_ptr, html_tag_option_title, prod_name_ptr);
		}
		count++;
	}
	
	sqlt_code = ::sqlite3_finalize(stmt_handle);
	#ifdef _DEBUG
	if( sqlt_code ) throw std::exception("'::sqlite3_finalize' failed in "__FUNCTION__);
	#endif
	// -- END SQL CODE ---------------------------

	::format(html_output_, "\t\t<select name=\"prod\" size=\"%1\" style=\"font-family: Tahoma; font-size: 12pt\">\r\n", (count>13)?13:count);
	html_output_.append(html_tag_select);
	html_output_.append("\t\t</select>\r\n");
}


/*
 *	Получаем в <radio>-таблицу все слоты оборудования prod_str
 *
 */
void UI_Control::sql_select_racks_for_prod(std::string const& prod_str) {
	//#ifdef _DEBUG
	//function func("        "__FUNCTION__);
	//#endif
	html_output_.append("\t\t<table cellspacing=\"0\" cellpadding=\"1\">\r\n");
	/*
 	::format(html_output_,
			//"\t\t<b>&ldquo;%1&rdquo;</b>, в составе:<br/>\r\n" 
			//"\t\t<b>%1</b>:<br/>\r\n" 
			"\t\t<table cellspacing=\"0\" cellpadding=\"1\">\r\n",
			prod_str);
	*/
	// -- BEGIN SQL CODE ---------------------------
	std::string sql_statement_utf8enc;
	::format(sql_statement_utf8enc, "select RACK_SLOT_PROD, RACK_SLOT_NAME, RACK_SLOT_NOTE from RACKS where RACK_PROD_ART='%1'", prod_str);
	#ifdef _DEBUG
	{std::string deb_out; ::format(deb_out, "\n    %1;\n\n", sql_statement_utf8enc); ::OutputDebugString(deb_out.c_str());}
	#endif

	sqlite3_stmt* stmt_handle(0);
	int sqlt_code = ::sqlite3_prepare_v2(
			::sqlite3_handle_global,         // Database handle
			sql_statement_utf8enc.c_str(),   // SQL UI_Viewment, UTF-8 encoded
			sql_statement_utf8enc.length(),  // Maximum length of zSql in bytes.
			&stmt_handle,                    // OUT: UI_Viewment handle
			0                                // OUT: Pointer to unused portion of zSql
			);
	if( sqlt_code ) throw std::exception("'::sqlite3_prepare_v2' failed in "__FUNCTION__);

	char const* desc_file_name = 0;
	while( 100==(sqlt_code=::sqlite3_step(stmt_handle)) ) {
		char const* const rack_type_ptr = ::sqlite3_column_bytes(stmt_handle, 0)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 0)):"null";
		char const* const rack_name_ptr = ::sqlite3_column_bytes(stmt_handle, 1)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 1)):"null";
		char const* const rack_note_ptr = ::sqlite3_column_bytes(stmt_handle, 2)>0
			?reinterpret_cast<char const* const>(::sqlite3_column_text(stmt_handle, 2)):"null";
		if( 1819047278!=*((long*)rack_type_ptr) && 1819047278!=*((long*)rack_name_ptr) ) {
			#ifdef _DEBUG
			//{std::string deb_out; ::format(deb_out, "    SQL_DATA(\"%1\", \"%2\", \"%3\")\r\n", rack_type_ptr, rack_name_ptr, rack_note_ptr); ::OutputDebugString(deb_out.c_str());}
			#endif
			::format(html_output_,
					"\t\t\t<tr><td><input type=\"radio\" name=\"slot\" value=\"%1\">%2</td><td>&nbsp;</td><td><font size=\"-1\"><i>%3</i></font></td></tr>\r\n",
					rack_type_ptr, rack_name_ptr, 1819047278!=*((long*)rack_note_ptr)?rack_note_ptr:"&nbsp;");
		}
	}

	sqlt_code = ::sqlite3_finalize(stmt_handle);
	#ifdef _DEBUG
	if( sqlt_code ) throw std::exception("'::sqlite3_finalize' failed in "__FUNCTION__);
	#endif
	// -- END SQL CODE ---------------------------

	html_output_.append("\t\t</table>\r\n");
}
