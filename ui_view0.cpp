#include "ui.hpp"
/// #include "db.hpp" //< для проверки имени пользователя и пароля

#include "../demay/format.hpp"
#include "../demay/scope_guard.hpp"

/*!	Обработчик сообщения '>' от формы Login
 *******************************************
 *	1) Проверить имя пользователя и пароль
 *	2) Сформировать главное меню ->
 *	например так:
 *	    prod_slot = '';
 *	    Automate::sql_select_prods_for_rack(slot) ->
 *	        select PROD_ART, PROD_NAME, PROD_NOTE from PRODUCTS where PROD_SLOT=''
 *	@param UI_Control_ указатель на автомат
 */
void UI_View0::ev_next(std::string& html_output, HttpArgs const& http_args, DB_Handle&) {
	#ifdef _DEBUG
	function func("\t"__FUNCTION__);
	#endif

	//! проверка имени пользователя и пароля
	if( "admin"==http_args("user") && "qwerty"==http_args("pass") ) {
		int next_view = 1; //!< на следущей итерации для приема аргументов будет создан View1
		::format(html_output,
				#ifdef _DEBUG
				"\r\n\t<!-- " __FUNCTION__ " -->\r\n\r\n"
				#endif
				"\t<form method=\"post\" enctype=\"multipart/form-data\">\r\n"
				"\t\t<input type=\"hidden\" name=\"view\" value=\"%1\">\r\n" 
				//"\t\t<input type=\"hidden\" name=\"auth\" value=\"%2\">\r\n"
				//"\t\t<input type=\"hidden\" name=\"user\" value=\"%3\">\r\n"
				//"\t\t<input type=\"submit\" name=\"btn\" value=\"<\" title=\"Назад\">\r\n"
				"\t\t<b><u>Главное меню</u></b><br/>\r\n"
				"\t\t<input type=\"submit\" name=\"btn\" value=\"1) Сверка счетов\" class=\"cell_btn\" title=\"Выбрать 1) Заявки\"/><br/>\r\n"
				//"\t\t<input type=\"submit\" name=\"btn\" value=\"2) Что-то еще\" class=\"cell_btn\" title=\"Выбрать 2) Что-то еще\"/><br/>\r\n"
				//"\t\t<input type=\"submit\" name=\"btn\" value=\"3) Что-то другое\" class=\"cell_btn\" title=\"Выбрать 3) Что-то другое\"/><br/>\r\n"
				"\t\t<input type=\"submit\" name=\"btn\" value=\"9) Настройка\" class=\"cell_btn\" title=\"Выбрать 9) Администрирование\"/><br/>\r\n"
				"\t</form>\r\n"
				, next_view
				//, http_args("auth")
				//, http_args("user")
		);
	} else html_output.assign("Неверное имя пользователя или пароль"); return;// throw std::runtime_error("Неверное имя пользователя или пароль"); 
}

