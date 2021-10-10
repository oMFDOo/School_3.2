

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    int i;
    static int select; TCHAR str[100]; //뱡항키 종류 결정할 변수
    RECT rect[4] = { {100,100,180,200}, {180,0,260,100}, {260,100,340,200}, {180,200,260,300} };
    TCHAR direct[4][10] = { _T("왼쪽"), _T("위쪽"), _T("오른쪽"), _T("아래쪽"), };
    HBRUSH hBrush, oldBrush;

    switch (iMsg)
    {
    case WM_CREATE:
        select = -1; return 0;
        break;

    case WM_PAINT: // 문자열출력 and 방향키따라서 다르게 출력 and
       // 누른방향키 기억-> keydown에서 기억
        hdc = BeginPaint(hwnd, &ps); //hdc 생성

        for (i = 0; i < 4; i++)
        {
            //사각형 그려라.
            Rectangle(hdc, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);

            // (글자 그려라)hdc에서, 1번째, 문자열길이, 위치지정(사각형), 사각형 내의 글자 위치지정
            DrawText(hdc, direct[i], _tcslen(direct[i]), &rect[i], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        }

        if (select == 0) _stprintf_s(str, _T("왼쪽 화살표를 누른다")); //문자열 만들어서 str에 저장
        else if (select == 1) _stprintf_s(str, _T("위쪽 화살표를 누른다"));
        else if (select == 2) _stprintf_s(str, _T("오른쪽 화살표를 누른다"));
        else if (select == 3) _stprintf_s(str, _T("아래쪽 화살표를 누른다"));

        if (select != -1)
        {
            TextOut(hdc, 0, 0, str, _tcslen(str)); // default 아니면 str 문자열 출력
        }



        EndPaint(hwnd, &ps);
        return 0;


    case WM_KEYDOWN:
        hdc = GetDC(hwnd);
        hBrush = CreateSolidBrush(RGB(255, 0, 0)); //브러쉬 생성
        oldBrush = (HBRUSH)SelectObject(hdc, hBrush); // 브러쉬 집음 : 사각형 만들어지면 자동으로 색칠함

        switch (wParam)
        {
        case VK_LEFT: select = 0; break; //방향키 0 1 2 3 / -1
        case VK_UP:   select = 1; break;
        case VK_RIGHT:select = 2; break;
        case VK_DOWN: select = 3; break;
        default:     select = -1; break;
            break;
        }
        SelectObject(hdc, oldBrush); //그리기 다 끝나면 oldbrush를 등록
        DeleteObject(hBrush); // hBrush 삭제(paint나올때마다 브러쉬 만들기때문에 메모리 소비가 커짐)
        break;

    case WM_KEYUP:
        InvalidateRgn(hwnd, NULL, TRUE); //특정영역 무효화 / 키 올라오면 내용 삭제해서 paint 실행(문자열 만들어짐)
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}