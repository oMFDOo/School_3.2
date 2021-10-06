

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    int i;
    static int select; TCHAR str[100]; //����Ű ���� ������ ����
    RECT rect[4] = { {100,100,180,200}, {180,0,260,100}, {260,100,340,200}, {180,200,260,300} };
    TCHAR direct[4][10] = { _T("����"), _T("����"), _T("������"), _T("�Ʒ���"), };
    HBRUSH hBrush, oldBrush;

    switch (iMsg)
    {
    case WM_CREATE:
        select = -1; return 0;
        break;

    case WM_PAINT: // ���ڿ���� and ����Ű���� �ٸ��� ��� and
       // ��������Ű ���-> keydown���� ���
        hdc = BeginPaint(hwnd, &ps); //hdc ����

        for (i = 0; i < 4; i++)
        {
            //�簢�� �׷���.
            Rectangle(hdc, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);

            // (���� �׷���)hdc����, 1��°, ���ڿ�����, ��ġ����(�簢��), �簢�� ���� ���� ��ġ����
            DrawText(hdc, direct[i], _tcslen(direct[i]), &rect[i], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        }

        if (select == 0) _stprintf_s(str, _T("���� ȭ��ǥ�� ������")); //���ڿ� ���� str�� ����
        else if (select == 1) _stprintf_s(str, _T("���� ȭ��ǥ�� ������"));
        else if (select == 2) _stprintf_s(str, _T("������ ȭ��ǥ�� ������"));
        else if (select == 3) _stprintf_s(str, _T("�Ʒ��� ȭ��ǥ�� ������"));

        if (select != -1)
        {
            TextOut(hdc, 0, 0, str, _tcslen(str)); // default �ƴϸ� str ���ڿ� ���
        }



        EndPaint(hwnd, &ps);
        return 0;


    case WM_KEYDOWN:
        hdc = GetDC(hwnd);
        hBrush = CreateSolidBrush(RGB(255, 0, 0)); //�귯�� ����
        oldBrush = (HBRUSH)SelectObject(hdc, hBrush); // �귯�� ���� : �簢�� ��������� �ڵ����� ��ĥ��

        switch (wParam)
        {
        case VK_LEFT: select = 0; break; //����Ű 0 1 2 3 / -1
        case VK_UP:   select = 1; break;
        case VK_RIGHT:select = 2; break;
        case VK_DOWN: select = 3; break;
        default:     select = -1; break;
            break;
        }
        SelectObject(hdc, oldBrush); //�׸��� �� ������ oldbrush�� ���
        DeleteObject(hBrush); // hBrush ����(paint���ö����� �귯�� ����⶧���� �޸� �Һ� Ŀ��)
        break;

    case WM_KEYUP:
        InvalidateRgn(hwnd, NULL, TRUE); //Ư������ ��ȿȭ / Ű �ö���� ���� �����ؼ� paint ����(���ڿ� �������)
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}