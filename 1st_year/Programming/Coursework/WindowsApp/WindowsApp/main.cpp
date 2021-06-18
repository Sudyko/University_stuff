#include <tchar.h>
#include <windows.h>
#include <CommCtrl.h>
#include <stdio.h>
#include "IdentStr.h"
#include "DecStr.h"
#include "typeinfo"
#include "string.h"
#include "str.h"

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_MENU;

    if (!RegisterClassEx(&wincl))
        return 0;

    hwnd = CreateWindowEx(
        0,
        szClassName,
        _T("Курcовая работа, Last_Name First_Name, группа №?, Вариант №20."),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1500,
        650,
        HWND_DESKTOP,
        NULL,
        hThisInstance,
        NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return (int)messages.wParam;
}

#define ID_BUTTON1 1
#define ID_BUTTON2 2
#define ID_BUTTON3 3
#define ID_EDIT1 4
#define ID_EDIT2 5
#define ID_EDIT3 6
#define ID_EDIT4 7
#define ID_EDIT5 8
HWND static1, static2, static3, static4, static5, static6, static7, static8, static9;
HWND button1, button2, button3;
HWND edit1, edit2, edit3, edit4, edit5, listedit;
HWND listview;
HWND radbutton1, radbutton2, radbutton3;
HWND combox1, combox2;
HINSTANCE hInst;
int size;
wchar_t b[10];
int a;
str** ptr;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        static1 = CreateWindow(TEXT("STATIC"), TEXT("Укажите количество элементов"),
            WS_CHILD | WS_VISIBLE,
            20, 30, 212, 23,
            hwnd, (HMENU)NULL, NULL, NULL);

        static2 = CreateWindow(TEXT("STATIC"), TEXT("Номер элемента"),
            WS_CHILD | WS_VISIBLE,
            675, 30, 110, 23,
            hwnd, (HMENU)NULL, NULL, NULL);

        static3 = CreateWindow(TEXT("STATIC"), TEXT("Укажите значение"),
            WS_CHILD | WS_VISIBLE,
            675, 160, 125, 23,
            hwnd, (HMENU)NULL, NULL, NULL);

        static4 = CreateWindow(TEXT("STATIC"), TEXT("Тестирование"),
            WS_CHILD | WS_VISIBLE,
            20, 380, 93, 23,
            hwnd, (HMENU)NULL, NULL, NULL);

        static5 = CreateWindow(TEXT("STATIC"), TEXT("Укажите тип для тестирования"),
            WS_CHILD | WS_VISIBLE,
            20, 425, 210, 20,
            hwnd, (HMENU)NULL, NULL, NULL);

        static6 = CreateWindow(TEXT("STATIC"), TEXT("Укажите метод для тестирования"),
            WS_CHILD | WS_VISIBLE,
            300, 425, 230, 20,
            hwnd, (HMENU)NULL, NULL, NULL);

        static7 = CreateWindow(TEXT("STATIC"), TEXT("Укажите № первого операнда"),
            WS_CHILD | WS_VISIBLE,
            650, 425, 207, 20,
            hwnd, (HMENU)NULL, NULL, NULL);

        static8 = CreateWindow(TEXT("STATIC"), TEXT("Укажите № второго операнда"),
            WS_CHILD | WS_VISIBLE,
            900, 425, 207, 20,
            hwnd, (HMENU)NULL, NULL, NULL);

        static9 = CreateWindow(TEXT("STATIC"), TEXT("ВЫВОД"),
            WS_CHILD | WS_VISIBLE,
            1275, 30, 55, 20,
            hwnd, (HMENU)NULL, NULL, NULL);

        edit1 = CreateWindow(TEXT("EDIT"), NULL,
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_NUMBER,
            245, 30, 50, 23,
            hwnd, (HMENU)ID_EDIT1, NULL, NULL);

        edit2 = CreateWindow(TEXT("EDIT"), NULL,
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_NUMBER,
            800, 30, 50, 23,
            hwnd, (HMENU)ID_EDIT2, NULL, NULL);

        edit3 = CreateWindow(TEXT("EDIT"), NULL,
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT | ES_MULTILINE,
            675, 190, 300, 100,
            hwnd, (HMENU)ID_EDIT3, NULL, NULL);

        edit4 = CreateWindow(TEXT("EDIT"), NULL,
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_NUMBER,
            700, 450, 100, 23,
            hwnd, (HMENU)ID_EDIT4, NULL, NULL);

        edit5 = CreateWindow(TEXT("EDIT"), NULL,
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_NUMBER,
            950, 450, 100, 23,
            hwnd, (HMENU)ID_EDIT5, NULL, NULL);

        radbutton1 = CreateWindow(TEXT("BUTTON"), TEXT("Str"),
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            675, 70, 40, 20,
            hwnd, (HMENU)101, NULL, NULL);

        radbutton2 = CreateWindow(TEXT("BUTTON"), TEXT("IdentStr"),
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            675, 95, 70, 20,
            hwnd, (HMENU)102, NULL, NULL);

        radbutton3 = CreateWindow(TEXT("BUTTON"), TEXT("DecStr"),
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            675, 120, 63, 20,
            hwnd, (HMENU)103, NULL, NULL);

        button1 = CreateWindow(TEXT("BUTTON"), TEXT("Установить"),
            WS_VISIBLE | WS_CHILD,
            310, 32, 100, 20,
            hwnd, (HMENU)ID_BUTTON1, NULL, NULL);

        button2 = CreateWindow(TEXT("BUTTON"), TEXT("Установить"),
            WS_VISIBLE | WS_CHILD,
            675, 300, 100, 20,
            hwnd, (HMENU)ID_BUTTON2, NULL, NULL);

        button3 = CreateWindow(TEXT("BUTTON"), TEXT("ТЕСТ"),
            WS_VISIBLE | WS_CHILD,
            825, 500, 100, 20,
            hwnd, (HMENU)ID_BUTTON3, NULL, NULL);

        listview = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | LVS_REPORT | WS_BORDER,
            20, 60, 600, 300,
            hwnd, (HMENU)NULL, NULL, NULL);

        listedit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD | ES_WANTRETURN | ES_MULTILINE | ES_READONLY,
            1150, 60, 300, 500,
            hwnd, (HMENU)NULL, NULL, NULL);

        HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Consolas"));
        SendMessage(listedit, WM_SETFONT, (WPARAM)hFont, NULL);

        combox1 = CreateWindow(TEXT("COMBOBOX"), NULL,
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            25, 450, 200, 200,
            hwnd, (HMENU)201, hInst, NULL);
        SendMessage(combox1, CB_ADDSTRING, 1, (LPARAM)_T("Str"));
        SendMessage(combox1, CB_ADDSTRING, 1, (LPARAM)_T("IdentStr"));
        SendMessage(combox1, CB_ADDSTRING, 1, (LPARAM)_T("DecStr"));

        combox2 = CreateWindow(TEXT("COMBOBOX"), NULL,
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            315, 450, 200, 200,
            hwnd, (HMENU)202, hInst, NULL);

        ListView_SetExtendedListViewStyle(listview, LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);

        LVCOLUMN lvc = { 0 };
        memset(&lvc, 0, sizeof(lvc));
        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvc.fmt = LVCFMT_LEFT;
        lvc.iSubItem = 0;
        lvc.pszText = (LPWSTR)_T("№");
        ListView_InsertColumn(listview, 0, &lvc);
        ListView_SetColumnWidth(listview, 0, 30);
        lvc.iSubItem = 1;
        lvc.pszText = (LPWSTR)_T("Тип");
        ListView_InsertColumn(listview, 1, &lvc);
        ListView_SetColumnWidth(listview, 1, 285);
        lvc.iSubItem = 2;
        lvc.pszText = (LPWSTR)_T("Значение");
        ListView_InsertColumn(listview, 2, &lvc);
        ListView_SetColumnWidth(listview, 2, 285);

        EnableWindow(edit2, FALSE); // edits
        EnableWindow(edit3, FALSE);
        EnableWindow(edit4, FALSE);
        EnableWindow(edit5, FALSE);
        EnableWindow(radbutton1, FALSE); // radbuttons
        EnableWindow(radbutton2, FALSE);
        EnableWindow(radbutton3, FALSE);
        EnableWindow(button2, FALSE); // buttons
        EnableWindow(button3, FALSE);
        EnableWindow(combox1, FALSE); // comboboxes
        EnableWindow(combox2, FALSE);
        break;
    };

    case WM_COMMAND: {
        LVITEM lv = { 0 };
        if (LOWORD(wParam) == ID_BUTTON1) {
            int len = SendMessage(edit1, WM_GETTEXTLENGTH, 0, 0);
            if (len != 0) {
                GetWindowText(edit1, b, 100);
                size = _wtoi(b);
                if (size > 15) {
                    SendMessageA(edit1, WM_SETTEXT, WPARAM(NULL), LPARAM("15"));
                    size = 15;
                }
                if (size == 0 || size < 0) {
                    SendMessageA(edit1, WM_SETTEXT, WPARAM(NULL), LPARAM("2"));
                    size = 2;
                }

                ptr = new str * [size];
                for (int i = 0; i < size; i++) { ptr[i] = new str(); }

                SetWindowTextA(listedit, concStr);
                EnableWindow(edit1, FALSE); // edits
                EnableWindow(edit2, TRUE);
                EnableWindow(edit3, TRUE);
                EnableWindow(radbutton1, TRUE); // radbuttons
                EnableWindow(radbutton2, TRUE);
                EnableWindow(radbutton3, TRUE);
                EnableWindow(button1, FALSE); // buttons
                EnableWindow(button2, TRUE);
                EnableWindow(button3, FALSE);
                EnableWindow(button3, TRUE);
                EnableWindow(combox1, TRUE); // comboboxes
                EnableWindow(combox2, TRUE);

                SendMessage(radbutton1, BM_SETCHECK, BST_CHECKED, 0);
                for (int i = 0; i < size; i++) {
                    lv.iItem = i;
                    ListView_InsertItem(listview, &lv);
                    swprintf_s(b, L"%d", i);
                    ListView_SetItemText(listview, i, 0, (LPWSTR)b);
                    ListView_SetItemText(listview, i, 1, (LPWSTR)_TEXT("Str"));
                }
            }
        }
        int Element;
        GetWindowText(edit2, b, 100);
        Element = _wtoi(b);
        wchar_t Val[256];
        GetWindowText(edit3, Val, 256);
        size_t Size;
        _locale_t localize = _create_locale(LC_ALL, "ru-RU");
        if (LOWORD(wParam) == ID_BUTTON2) {
            int len = SendMessage(edit3, WM_GETTEXTLENGTH, 0, 0);
            int lenN = SendMessage(edit2, WM_GETTEXTLENGTH, 0, 0);
            if ((lenN != 0) && (len != 0) && Element >= 0 && Element <= size - 1) {
                char cs[256];
                GetWindowText(edit3, Val, 256);
                _wcstombs_s_l(&Size, cs, Val, 256, localize);
                if (SendMessage(radbutton1, BM_GETCHECK, 0, 0) == 1) {
                    ListView_SetItemText(listview, Element, 1, (LPWSTR)_TEXT("Str"));
                    ptr[Element] = new str(cs);
                    SetWindowTextA(listedit, concStr);
                }
                else if (SendMessage(radbutton2, BM_GETCHECK, 0, 0)) {
                    ListView_SetItemText(listview, Element, 1, (LPWSTR)_TEXT("IdentStr"));
                    ptr[Element] = new IdentStr(cs);
                    SetWindowTextA(listedit, concStr);
                }
                else if (SendMessage(radbutton3, BM_GETCHECK, 0, 0)) {
                    ListView_SetItemText(listview, Element, 1, (LPWSTR)_TEXT("DecStr"));
                    ptr[Element] = new DecStr(cs);
                    SetWindowTextA(listedit, concStr);
                }
                _mbstowcs_s_l(&Size, Val, (*ptr[Element]).Getstr(), (*ptr[Element]).Getlen(), localize);
                ListView_SetItemText(listview, Element, 2, (LPWSTR)Val);
            }
        }
        // Resources for operator's combobox
        if (LOWORD(wParam) == 201) {
            SendMessageA(edit4, WM_SETTEXT, WPARAM(NULL), LPARAM(""));
            SendMessageA(edit5, WM_SETTEXT, WPARAM(NULL), LPARAM(""));
            EnableWindow(edit4, FALSE);
            EnableWindow(edit5, FALSE);

            SendMessage(combox2, CB_RESETCONTENT, 0, 0);
            SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("show()"));
            SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("operator="));

            if (SendMessage(combox1, CB_GETCURSEL, 0, 0) == 0) {
                SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("operator~"));
                SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("clear"));
            }
            else if (SendMessage(combox1, CB_GETCURSEL, 0, 0) == 1) {
                SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("operator+"));
                SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("operator~"));
                SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("operator[]"));
                SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("operator=="));
            }
            else if (SendMessage(combox1, CB_GETCURSEL, 0, 0) == 2) {
                SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("operator+"));
                SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("operator-"));
                SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("operator=="));
                SendMessage(combox2, CB_ADDSTRING, 1, (LPARAM)_TEXT("canchar"));
            }
        }
        // Opening windows
        if (LOWORD(wParam) == 202 && SendMessage(combox1, CB_GETCURSEL, 0, 0) == 0) { // STR
            SendMessageA(edit4, WM_SETTEXT, WPARAM(NULL), LPARAM(""));
            SendMessageA(edit5, WM_SETTEXT, WPARAM(NULL), LPARAM(""));
            EnableWindow(edit4, TRUE);
            if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 0) { EnableWindow(edit5, FALSE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 1) { EnableWindow(edit5, TRUE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 2) { EnableWindow(edit5, FALSE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 3) { EnableWindow(edit5, FALSE); }
        }
        if (LOWORD(wParam) == 202 && SendMessage(combox1, CB_GETCURSEL, 0, 0) == 1) { // IDENT STR
            SendMessageA(edit4, WM_SETTEXT, WPARAM(NULL), LPARAM(""));
            SendMessageA(edit5, WM_SETTEXT, WPARAM(NULL), LPARAM(""));
            EnableWindow(edit4, TRUE);
            if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 0) { EnableWindow(edit5, FALSE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 1) { EnableWindow(edit5, TRUE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 2) { EnableWindow(edit5, TRUE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 3) { EnableWindow(edit5, FALSE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 4) { EnableWindow(edit5, TRUE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 5) { EnableWindow(edit5, TRUE); }
        }
        if (LOWORD(wParam) == 202 && SendMessage(combox1, CB_GETCURSEL, 0, 0) == 2) { // DEC STR
            SendMessageA(edit4, WM_SETTEXT, WPARAM(NULL), LPARAM(""));
            SendMessageA(edit5, WM_SETTEXT, WPARAM(NULL), LPARAM(""));
            EnableWindow(edit4, TRUE);
            if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 0) { EnableWindow(edit5, FALSE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 1) { EnableWindow(edit5, TRUE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 2) { EnableWindow(edit5, TRUE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 3) { EnableWindow(edit5, TRUE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 4) { EnableWindow(edit5, TRUE); }
            else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 5) { EnableWindow(edit5, FALSE); }
        }
        // Testing operators
        int len = SendMessage(edit4, WM_GETTEXTLENGTH, 0, 0);
        int len2 = SendMessage(edit5, WM_GETTEXTLENGTH, 0, 0);
        int operand1, operand2;
        if (LOWORD(wParam) == ID_BUTTON3 && len != 0) {
            GetWindowText(edit4, b, 100);
            operand1 = _wtoi(b);
            if (SendMessage(combox1, CB_GETCURSEL, 0, 0) == 0 && operand1 >= 0 && operand1 <= size - 1 && (typeid(*ptr[operand1]) == typeid(str))) {
                GetWindowText(edit5, b, 100);
                operand2 = _wtoi(b);
                if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 0) { // show() (str)
                    (ptr[operand1])->show();
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 1 && len2 != 0 && operand2 >= 0 && operand2 <= size - 1 && (typeid(*ptr[operand2]) == typeid(str))) { // operator= (str)
                    *(ptr[operand1]) = *(ptr[operand2]);
                    _mbstowcs_s_l(&Size, Val, (*ptr[operand1]).Getstr(), (*ptr[operand1]).Getlen(), localize);
                    ListView_SetItemText(listview, operand1, 2, (LPWSTR)Val);
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 2) { // operator~ (str)
                    str action = ~(*ptr[operand1]);
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 3) { // clear (str)
                    (ptr[operand1])->clear();
                    ListView_SetItemText(listview, operand1, 2, (LPWSTR)_TEXT(""));
                }
                SetWindowTextA(listedit, concStr);
            }
            else if (SendMessage(combox1, CB_GETCURSEL, 0, 0) == 1 && operand1 >= 0 && operand1 <= size - 1 && (typeid(*ptr[operand1]) == typeid(IdentStr))) {
                GetWindowText(edit5, b, 100);
                operand2 = _wtoi(b);
                if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 0) { // show() (IdentStr)
                    (ptr[operand1])->show();
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 1 && len2 != 0 && operand2 >= 0 && operand2 <= size - 1 && (typeid(*ptr[operand2]) == typeid(IdentStr))) { // operator= (IdentStr)
                    (*(dynamic_cast<IdentStr*>(ptr[operand1])) = *(dynamic_cast<IdentStr*>(ptr[operand2]))).get();
                    _mbstowcs_s_l(&Size, Val, (*ptr[operand1]).Getstr(), (*ptr[operand1]).Getlen(), localize);
                    ListView_SetItemText(listview, operand1, 2, (LPWSTR)Val);
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 2 && len2 != 0 && operand2 >= 0 && operand2 <= size - 1 && (typeid(*ptr[operand2]) == typeid(IdentStr))) { // operator+ (IdentStr)
                    conc((*(dynamic_cast<IdentStr*>(ptr[operand1])) + *(dynamic_cast<IdentStr*>(ptr[operand2]))).Getstr());
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 3) { // operator~ (IdentStr)
                    IdentStr action = ~(*ptr[operand1]);
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 4 && len2 != 0 && operand2 >= 0 && operand2 < (ptr[operand1])->Getlen()) { // operator[] (IdentStr)
                    (*(dynamic_cast<IdentStr*>(ptr[operand1])))[operand2];
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 5 && len2 != 0 && operand2 >= 0 && operand2 <= size - 1 && (typeid(*ptr[operand2]) == typeid(IdentStr))) { // operator== (IdentStr)
                    (*(dynamic_cast<IdentStr*>(ptr[operand1])) == *(dynamic_cast<IdentStr*>(ptr[operand2])));
                }
                SetWindowTextA(listedit, concStr);
            }
            else if (SendMessage(combox1, CB_GETCURSEL, 0, 0) == 2 && operand1 >= 0 && operand1 <= size - 1 && (typeid(*ptr[operand1]) == typeid(DecStr))) {
                GetWindowText(edit5, b, 100);
                operand2 = _wtoi(b);
                if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 0) { // show() (DecStr)
                    (ptr[operand1])->show();
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 1 && len2 != 0 && operand2 >= 0 && operand2 <= size - 1 && (typeid(*ptr[operand2]) == typeid(DecStr))) { // operator= (DecStr)
                    (*(dynamic_cast<DecStr*>(ptr[operand1])) = *(dynamic_cast<DecStr*>(ptr[operand2]))).get();
                    _mbstowcs_s_l(&Size, Val, (*ptr[operand1]).Getstr(), (*ptr[operand1]).Getlen(), localize);
                    ListView_SetItemText(listview, operand1, 2, (LPWSTR)Val);
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 2 && len2 != 0 && operand2 >= 0 && operand2 <= size - 1 && (typeid(*ptr[operand2]) == typeid(DecStr))) { // operator+ (DecStr)
                    conc((*(dynamic_cast<DecStr*>(ptr[operand1])) + *(dynamic_cast<DecStr*>(ptr[operand2]))).get());
                    DecChB = true;
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 3 && len2 != 0 && operand2 >= 0 && operand2 <= size - 1 && (typeid(*ptr[operand2]) == typeid(DecStr))) { // operator- (DecStr)
                    conc((*(dynamic_cast<DecStr*>(ptr[operand1])) - *(dynamic_cast<DecStr*>(ptr[operand2]))).get());
                    DecChB = true;
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 4 && len2 != 0 && operand2 >= 0 && operand2 <= size - 1 && (typeid(*ptr[operand2]) == typeid(DecStr))) { // operator== (DecStr)
                    (*(dynamic_cast<DecStr*>(ptr[operand1])) == *(dynamic_cast<DecStr*>(ptr[operand2])));
                }
                else if (SendMessage(combox2, CB_GETCURSEL, 0, 0) == 5) { // canchar (DecStr)
                    (dynamic_cast<DecStr*>(ptr[operand1]))->canchar();
                }
                SetWindowTextA(listedit, concStr);
            }
        }
        break;
    };
    case WM_CLOSE:
        if (MessageBox(hwnd, _T("Вы уверены?"), _T("Выход"), MB_YESNO | MB_ICONQUESTION) == IDYES) {
            for (int i = 0; i < size; i++) { delete ptr[i]; }
            delete[] concStr;
            delete[] ptr;
            DestroyWindow(hwnd);
        } break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default: return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}