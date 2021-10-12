//#include <iostream>
//using namespace std;
//
//class FruitSeller {
//private:
//    int price;
//    int amount;
//    int bank;
//public:
//    FruitSeller(int p, int a, int b);
//    void SalesApples(int cnt);
//    int HowMuchIsIt();
//    void ShowSalesResult();
//};
//FruitSeller::FruitSeller(int p, int a, int b) : price(p), amount(a), bank(b) {
//}
//void FruitSeller::SalesApples(int cnt) {
//    amount = amount - cnt;
//    bank = bank + (price * cnt);
//}
//int FruitSeller::HowMuchIsIt() {
//    return price;
//}
//void FruitSeller::ShowSalesResult() {
//    cout << "���� ���: " << amount << "��" << endl;
//    cout << "�Ǹ� ����: " << bank << "��" << endl;
//}
//class FruitBuyer {
//private:
//    int money;
//    int apple;
//public:
//    FruitBuyer(int money, int apple);
//    void BuyApples(FruitSeller& anotherSeller, int money);
//    void ShowBuyResult();
//};
//FruitBuyer::FruitBuyer(int money, int apple) : money(money), apple(apple) {
//
//}
//void FruitBuyer::BuyApples(FruitSeller& anotherSeller, int cnt) {
//    int price = anotherSeller.HowMuchIsIt();
//    if (price * cnt > money) {
//        cout << "�ܾ� ����" << endl;
//        return;
//    }
//    anotherSeller.SalesApples(cnt);
//    money -= price * cnt;
//    apple += cnt;
//}
//void FruitBuyer::ShowBuyResult() {
//    cout << "��� ����: " << apple << "��" << endl;
//    cout << "�ܾ�: " << money << "��" << endl;
//}
//void P3(void) {
//    FruitSeller seller(1000, 20, 0);
//    FruitBuyer buyer(5000, 0);
//    buyer.BuyApples(seller, 7);
//
//    cout << "���� �Ǹ����� ��Ȳ" << endl;
//    seller.ShowSalesResult();
//
//    cout << "���� �������� ��Ȳ" << endl;
//    buyer.ShowBuyResult();
//}
//int main() {
//    P3();
//    return 0;
//}