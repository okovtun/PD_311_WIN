https://github.com/okovtun/PD_311_WIN.git
https://www.youtube.com/playlist?list=PLeqyOOqxeiIPIp_IrqD5aXudCHnPU4vcA

Book:
https://github.com/maybez/maybe/blob/master/Books/windows/Windows%20Via%20C%EF%BC%8FC++,Fifth%20Edition%20.pdf
https://github.com/micros-uz/csharp/blob/master/Level%201/Books/Microsoft.Press.CLR.via.Csharp.4th.Edition.Oct.2012.pdf
https://777russia.ru/book/uploads/%D0%9F%D0%A0%D0%9E%D0%93%D0%A0%D0%90%D0%9C%D0%9C%D0%98%D0%A0%D0%9E%D0%92%D0%90%D0%9D%D0%98%D0%95/C%23/CLR%20via%20C%23%20%28.NET%204.5%29%2C%204th%20Edition%202012%20%28%D0%BE%D1%80%D0%B8%D0%B3%D0%B8%D0%BD%D0%B0%D0%BB%29.pdf

TODO:
1. В Solution 'WinAPI' добавить проект 'ListBox', и выполнить все те же действия, 
   которые были выполнены с ComboBox;
2. В проект 'ListBox' добавить две кнопки:
	"Добавить" - добавляет элемент в ListBox;
	"Удалить"  - Удаляет выбранный элемент из ListBox;
3. В этот же проект добавить галочку "Сортировка",
   которая включает и отключает сортировку ListBox;

DONE:
1. При запуске программы (проект 'WinAPI') в поле 'IDC_EDIT_LOGIN' должно отображаться приглашение:		DONE
   'Введите логин'. Когда пользователь заходит в это поле, приглашение пропадает, и если пользователь
   ввел свое имя, то оно сохраняется в этом поле, но если пользователь оставил поле пустым, 
   и перешел на другой элемент интерфейса, то принлашение снова появляется;
2. В проекте 'ComboBox' при нажатии на кнопку 'OK' должен появляться MessageBox и отображать сообщение:
   "Вы выбрали пункт №3 со значением 'first'";