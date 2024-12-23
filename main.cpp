#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
class Pair
{
public:
    int first;
    int second;
    Pair() : first(0), second(0) {}
    Pair(int a, int b) : first(a), second(b) {}
};
void wypisz_tablice_na_odwrot(int* tab, int rozmiar);
class Pole
{
public:
    int info;
    Pole* nast;
    Pole(int dana) : info(dana), nast(nullptr) {}
};
class Lista
{
    Pole* glowa;
    Pole* ogon;
public:
    Lista()
    {
        glowa = nullptr;
        ogon = nullptr;
    }
    void dodajPoleStart(int dana)
    {
        Pole* nowy = new Pole(dana);
        if (glowa == nullptr)
        {
            glowa = nowy;
            ogon = nowy;
        }
        else
        {
            nowy->nast = glowa;
            glowa = nowy;
        }
    }
    /*void dodajPoleKoniec(int dana)
    {
        Pole* nowy = new Pole(dana);
        if (glowa == nullptr)
        {
            glowa = nowy;
            ogon = nowy;
        }
        else
        {
            ogon->nast = nowy;
            ogon = nowy;
        }
    }*/
    void usunGlowe()
    {
        if (glowa == nullptr)
            return;
        Pole* tmp = glowa;
        glowa = glowa->nast;
        delete tmp;
    }
    /*void wyswietl() const
    {
        Pole* tmp = glowa;
        while (tmp != nullptr)
        {
            printf("%d ", tmp->info);
            tmp = tmp->nast;
        }
        printf("\n");
    }*/
    int zwrocPierwszy() const
    {
        if (glowa != nullptr)
            return glowa->info;
        else return 0;
    }
    bool Pusty() const
    {
        if (glowa == nullptr)
            return true;
        else return false;
    }
    ~Lista()
    {
        while (glowa != nullptr)
        {
            Pole* tmp = glowa;
            glowa = tmp->nast;
            delete tmp;
        }
    }
};

class Wezel
{
public:
    int liczba_sasiadow;
    int* sasiedzi;
    Wezel() : liczba_sasiadow(0), sasiedzi(nullptr) {}
    void set_sasiedzi(int ile, int* s)
    {
        liczba_sasiadow = ile;
        sasiedzi = new int[ile];
        for (int i = 0; i < ile; ++i)
        {
            sasiedzi[i] = s[i];
        }
    }
    /*void wypisz() const
    {
        cout << "Ma " << liczba_sasiadow << " sasiadow : ";
        for (int i = 0; i < liczba_sasiadow; i++)
        {
            cout << sasiedzi[i] << " ";
        }
        cout << endl;
    }*/
    ~Wezel() {
        delete[] sasiedzi;
    }
};

class Graf
{
public:
    enum strona
    {
        lewo,
        prawo,
        brak,
    };
    int liczba_wezlow;
    Wezel* wezly;
    bool* odwiedzone;
    strona* umieszczenie;
    int* kolory;
    int* posortowane_wezly;
    int* kilkukrotne_odwiedzanie;
    int* wezly_w_skladowej;
    Graf(int ile) : liczba_wezlow(ile)
    {
        wezly = new Wezel[ile + 1];
        odwiedzone = new bool[ile + 1];
        umieszczenie = new strona[ile + 1];
        kolory = new int[ile + 1];
        posortowane_wezly = new int[ile + 1];
        kilkukrotne_odwiedzanie = new int[ile + 1];
        wezly_w_skladowej = new int[ile + 1];
        for (int i = 1; i <= ile; i++)
        {
            odwiedzone[i] = false;
            umieszczenie[i] = brak;
            kolory[i] = -1; //niepokolorowane
            posortowane_wezly[i] = i;
            kilkukrotne_odwiedzanie[i] = 0;
            wezly_w_skladowej[i] = 0;
        }
    }
    /*void wypisz_graf()
    {
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            cout << "Wezel nr" << i << ": ";
            wezly[i].wypisz();
        }
    }*/
    void dfs(int obecny)
    {
        Lista stos;
        Lista jakie_byly;
        stos.dodajPoleStart(obecny);
        jakie_byly.dodajPoleStart(obecny);
        odwiedzone[obecny] = true;
        int licz_wezly = 1;
        while (!stos.Pusty())
        {
            int obrabiany = stos.zwrocPierwszy();
            stos.usunGlowe();
            for (int i = 0; i < wezly[obrabiany].liczba_sasiadow; i++)
            {
                int sasiad = wezly[obrabiany].sasiedzi[i];
                if (!odwiedzone[sasiad])
                {
                    stos.dodajPoleStart(sasiad);
                    jakie_byly.dodajPoleStart(sasiad);
                    odwiedzone[sasiad] = true;
                    licz_wezly++;
                }
            }
        }
        while (!jakie_byly.Pusty())
        {
            int wezel = jakie_byly.zwrocPierwszy();
            jakie_byly.usunGlowe();
            wezly_w_skladowej[wezel] = licz_wezly;
        }
    }
    bool dfs_dwudzielny(int obecny)
    {
        Lista stos;
        stos.dodajPoleStart(obecny);
        while (!stos.Pusty())
        {
            int obrabiany = stos.zwrocPierwszy();
            stos.usunGlowe();
            if (!odwiedzone[obrabiany])
                odwiedzone[obrabiany] = true;
            for (int i = 0; i < wezly[obrabiany].liczba_sasiadow; i++)
            {
                int sasiad = wezly[obrabiany].sasiedzi[i];
                if (umieszczenie[sasiad] == umieszczenie[obrabiany] && odwiedzone[sasiad] == true)
                    return false;
                else if (umieszczenie[sasiad] == brak && odwiedzone[sasiad] == false)
                {
                    if (umieszczenie[obrabiany] == lewo)
                        umieszczenie[sasiad] = prawo;
                    else
                        umieszczenie[sasiad] = lewo;
                }
                if (!odwiedzone[sasiad])
                {
                    stos.dodajPoleStart(sasiad);
                    odwiedzone[sasiad] = true;
                }
            }
        }
        return true;
    }
    template<typename T, typename Compare>
    void heapify(T* tab, int rozmiar, int korzen, Compare cmp)
    {
        int najwiekszy = korzen;
        int left = 2 * korzen + 1;
        int right = 2 * korzen + 2;
        if (left < rozmiar && cmp(tab[left], tab[najwiekszy]))
            najwiekszy = left;
        if (right < rozmiar && cmp(tab[right], tab[najwiekszy]))
            najwiekszy = right;
        if (najwiekszy != korzen) {
            T temp = tab[najwiekszy];
            tab[najwiekszy] = tab[korzen];
            tab[korzen] = temp;
            heapify(tab, rozmiar, najwiekszy, cmp);
        }
    }
    template<typename T, typename Compare>
    void heapsort(T* tab, int rozmiar, Compare cmp)
    {
        for (int i = rozmiar / 2 - 1; i >= 0; i--) {
            heapify(tab, rozmiar, i, cmp);
        }
        for (int i = rozmiar - 1; i >= 0; i--) {
            T temp = tab[i];
            tab[i] = tab[0];
            tab[0] = temp;
            heapify(tab, i, 0, cmp);
        }
    }
    static bool cmp_int(int a, int b)
    {
        return a > b;
    }
    static bool cmp_Pair(Pair& a, Pair& b)
    {
        return a.first > b.first || (a.first == b.first && a.second < b.second);
    }
    void ciag_stopniowy()
    {
        int* ciag_stopniowy = new int[liczba_wezlow];
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            ciag_stopniowy[i - 1] = wezly[i].liczba_sasiadow;
        }
        heapsort(ciag_stopniowy, liczba_wezlow, cmp_int);
        wypisz_tablice_na_odwrot(ciag_stopniowy, liczba_wezlow);
        delete[] ciag_stopniowy;
    }
    void skladowe_spojnosci()
    {
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            odwiedzone[i] = false;
        }
        int ile_odwiedzonych = 0;
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            if (odwiedzone[i] == false)
            {
                ile_odwiedzonych++;
                dfs(i);
            }
        }
        printf("%d\n", ile_odwiedzonych);
    }
    bool dwudzielnosc()
    {
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            odwiedzone[i] = false;
            umieszczenie[i] = brak;
        }
        umieszczenie[1] = lewo; // pierwszy niech na lewo jego sasiedzi na prawo
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            if (odwiedzone[i] == false)
            {
                if (!dfs_dwudzielny(i))
                    return false;
            }
        }
        return true;
    }
    int bfs(int start, int ile_wezlow_w_skladowej)
    {
        int* kolejka = new int[liczba_wezlow + 1]; // kolejka nie na liscie bo za wolna
        int* odleglosci = new int[liczba_wezlow + 1]; // bez zerowania by oszczedzic czas
        int ktory_raz = kilkukrotne_odwiedzanie[start] + 1;
        kilkukrotne_odwiedzanie[start] = ktory_raz;
        odleglosci[start] = 0;
        kolejka[0] = start;
        int wez_z_kolejki = 0, zapisz_do_kolejki = 1;
        int max_odleglosc = 0, ile_dodano = 1;
        while (ile_dodano != ile_wezlow_w_skladowej)
        {
            int obrabiany = kolejka[wez_z_kolejki++]; //plus plus jest pozniej
            for (int i = 0; i < wezly[obrabiany].liczba_sasiadow; i++)
            {
                int sasiad = wezly[obrabiany].sasiedzi[i];
                if (kilkukrotne_odwiedzanie[sasiad] != ktory_raz)
                {
                    ile_dodano++;
                    kilkukrotne_odwiedzanie[sasiad] = ktory_raz;
                    odleglosci[sasiad] = odleglosci[obrabiany] + 1;
                    kolejka[zapisz_do_kolejki++] = sasiad;
                    if (odleglosci[sasiad] > max_odleglosc)
                        max_odleglosc = odleglosci[sasiad];
                }
            }
        }
        delete[] kolejka;
        delete[] odleglosci;
        return max_odleglosc;
    }
    void acentrycznosc()
    {
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            printf("%d ", bfs(i, wezly_w_skladowej[i]));
        }
        printf("\n");
    }
    void kolorowanie_greedy()
    {
        int* tablica_do_mex = new int[liczba_wezlow + 2];// moze byc o jeden kolor wiecej
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            kolory[i] = -1;
        }
        for (int i = 1; i <= liczba_wezlow + 1; i++)
        {
            tablica_do_mex[i] = -1;
        }
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            //przejdz po sasiadach i oznacz kolor zajetym dla danego wezla
            for (int j = 0; j < wezly[i].liczba_sasiadow; j++)
            {
                int sasiad = wezly[i].sasiedzi[j];
                int kolor_sasiada = kolory[sasiad];
                if (kolor_sasiada > 0)
                    tablica_do_mex[kolor_sasiada] = i; //oznaczenie ze w talbicy bedzie nr wierzcholka
            }
            int mex = 1;
            while (tablica_do_mex[mex] == i)//wyrzuci najmniejsza liczbe ktora nie jest oznaczona dla danego wierzcholka
                mex++;
            kolory[i] = mex;
        }
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            printf("%d ", kolory[i]);
        }
        printf("\n");
        delete[] tablica_do_mex;
    }
    void kolorowanie_LF()
    {
        Pair* kolejnosc = new Pair[liczba_wezlow];
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            Pair para(wezly[i].liczba_sasiadow, i);
            kolejnosc[i - 1] = para;
        }
        heapsort(kolejnosc, liczba_wezlow, cmp_Pair);
        for (int i = 0; i < liczba_wezlow; i++)
        {
            posortowane_wezly[liczba_wezlow - i] = kolejnosc[i].second;
        }
        int* tablica_do_mex = new int[liczba_wezlow + 2];
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            kolory[i] = -1;
        }
        for (int i = 1; i <= liczba_wezlow + 1; i++)
        {
            tablica_do_mex[i] = -1; // moze byc o jeden kolor wiecej
        }
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            //przejdz po sasiadach i wez ich kolory wrzuc do tabmex
            for (int j = 0; j < wezly[posortowane_wezly[i]].liczba_sasiadow; j++)
            {
                int sasiad = wezly[posortowane_wezly[i]].sasiedzi[j];
                int kolor_sasiada = kolory[sasiad];
                if (kolor_sasiada > 0)
                    tablica_do_mex[kolor_sasiada] = i;
            }
            int mex = 1;
            while (tablica_do_mex[mex] == i)//wyrzuci najmniejsza liczbe ktora nie wystapila
                mex++;
            kolory[posortowane_wezly[i]] = mex;
        }
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            printf("%d ", kolory[i]);
        }
        printf("\n");
        delete[] kolejnosc;
        delete[] tablica_do_mex;
    }
    void podgrafy() {
        long long int wynik = 0;
        int numeroznacz = 0;
        int* oznacz = new int[liczba_wezlow + 1];
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            oznacz[i] = -1;
            odwiedzone[i] = false;
        }

        int* jakie_byly = new int[liczba_wezlow + 1];
        for (int obecny = 1; obecny <= liczba_wezlow; obecny++)
        {
            if (!odwiedzone[obecny])
            {
                int indekskoniec = 1; // tylko w skladowej spojnosci (test 7)
                int poczstosu = 0;
                int* stos = new int[liczba_wezlow + 1]; //na tablicy bo szybciej
                stos[indekskoniec - 1] = obecny;
                jakie_byly[indekskoniec++] = obecny;
                odwiedzone[obecny] = true;
                int ile_dodano = 1;

                while (ile_dodano != wezly_w_skladowej[obecny])
                {
                    int obrabiany = stos[poczstosu];
                    poczstosu++;
                    for (int i = 0; i < wezly[obrabiany].liczba_sasiadow; i++)
                    {
                        int sasiad = wezly[obrabiany].sasiedzi[i];
                        if (!odwiedzone[sasiad])
                        {
                            stos[indekskoniec - 1] = sasiad;
                            indekskoniec++;
                            ile_dodano++;
                            jakie_byly[indekskoniec - 1] = sasiad;
                            odwiedzone[sasiad] = true;
                        }
                    }
                }
                for (int i = 1; i < indekskoniec; i++)
                {
                    numeroznacz++;
                    int aktualny = jakie_byly[i];
                    for (int k = 0; k < wezly[aktualny].liczba_sasiadow; k++)
                    {
                        int sasiad = wezly[aktualny].sasiedzi[k];
                        oznacz[sasiad] = numeroznacz;
                    }
                    for (int j = i + 1; j < indekskoniec; j++)
                    {
                        int liczwspolnych = 0;
                        int sasiedzi_j = jakie_byly[j];
                        for (int k = 0; k < wezly[sasiedzi_j].liczba_sasiadow; k++)
                        {
                            int sasiad = wezly[sasiedzi_j].sasiedzi[k];
                            if (oznacz[sasiad] == numeroznacz)
                                liczwspolnych++;
                        }
                        wynik += ((liczwspolnych) * (liczwspolnych - 1) / 2);
                    }
                }
                delete[] stos;
            }
        }

        printf("%lld\n", wynik / 2);
        delete[] oznacz;
        delete[] jakie_byly;
    }
    void liczba_dopelnienia() const
    {
        long long int ll = liczba_wezlow;
        long long int wszystkie = ll * (ll - 1) / 2;
        long long int obecne = 0;
        for (int i = 1; i <= liczba_wezlow; i++)
        {
            obecne += (wezly[i].liczba_sasiadow);
        }
        printf("%lld\n", wszystkie - obecne / 2);
    }
    ~Graf()
    {
        delete[] wezly;
        delete[] odwiedzone;
        delete[] kolory;
        delete[] umieszczenie;
        delete[] posortowane_wezly;
        delete[] kilkukrotne_odwiedzanie;
        delete[] wezly_w_skladowej;
    }
};
void wypisz_tablice_na_odwrot(int* tab, int rozmiar)
{
    for (int i = rozmiar - 1; i >= 0; i--)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}
void wypisz_odpowiedzi(Graf& graf)
{
    //graf.wypisz_graf();
    graf.ciag_stopniowy();
    graf.skladowe_spojnosci();
    if (graf.dwudzielnosc())
        printf("T\n");
    else
        printf("F\n");
    graf.acentrycznosc();
    //printf("?\n");
    printf("?\n");
    graf.kolorowanie_greedy();
    graf.kolorowanie_LF();
    printf("?\n");
    graf.podgrafy();
    //printf("?\n");
    graf.liczba_dopelnienia();
}
void wczytaj()
{
    int liczba_wierzcholkow;
    scanf("%d", &liczba_wierzcholkow);
    Graf graf(liczba_wierzcholkow);
    for (int i = 0; i < liczba_wierzcholkow; i++)
    {
        int stopien;
        scanf("%d", &stopien);
        int* sasiedzi = new int[stopien];
        for (int j = 0; j < stopien; j++)
        {
            scanf("%d", &sasiedzi[j]);
        }
        graf.wezly[i + 1].set_sasiedzi(stopien, sasiedzi); //indeksowanie od 1
        delete[] sasiedzi;
    }
    wypisz_odpowiedzi(graf);
}
int main()
{
    int testy;
    scanf("%d", &testy);
    while (testy--)
    {
        wczytaj();
    }
    return 0;
}
