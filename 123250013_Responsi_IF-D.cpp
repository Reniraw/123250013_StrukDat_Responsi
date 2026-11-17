#include <iostream>

using namespace std;

struct nodeQueue
{
    int kode;
    string nama;
    nodeQueue *next;
};

struct nodeStack
{
    int kode;
    string nama;
    nodeStack *next;
};

struct nodeTree
{
    int kode;
    string nama;
    nodeTree *kiri;
    nodeTree *kanan;
};

nodeQueue *front = NULL;
nodeQueue *last = NULL;
nodeStack *top = NULL;
nodeTree *root = NULL;

nodeTree *tambah_tree(nodeTree *akar, int kode, string nama)
{
    if (akar == NULL)
    {
        return new nodeTree{kode, nama, NULL, NULL};
    }
    if (kode < akar->kode)
    {
        akar->kiri = tambah_tree(akar->kiri, kode, nama);
    }
    else
    {
        akar->kanan = tambah_tree(akar->kanan, kode, nama);
    }
    return akar;
}

nodeTree *hapus_tree(nodeTree *akar, int kode)
{
    if (akar == NULL)
    {
        return NULL;
    }
    if (kode < akar->kode)
    {
        akar->kiri = hapus_tree(akar->kiri, kode);
    }
    else if (akar->kiri == NULL)
    {
        nodeTree *sisa = akar->kanan;
        delete akar;
        return sisa;
    }
    else if (akar->kanan == NULL)
    {
        nodeTree *sisa = akar->kiri;
        delete akar;
        return sisa;
    }
    else
    {
        nodeTree *pengganti = akar->kanan;
        while (pengganti->kiri != NULL)
        {
            pengganti = pengganti->kiri;
        }
        akar->kode = pengganti->kode;
        akar->nama = pengganti->nama;
        akar->kanan = hapus_Tree(akar->kanan, pengganti->kode);
    }
    return akar;
}

nodeTree *cari_tree(nodeTree *akar, int kode)
{
    if (akar == NULL)
    {
        return NULL;
    }
    if (kode == akar->kode)
    {
        return akar;
    }
    if (kode < akar->kode)
    {
        return cari_tree(akar->kiri, kode);
    }
    else
    {
        return cari_tree(akar->kanan, kode);
    }

    void preorder(nodeTree * akar, int &no)
    {
        if (akar == NULL)
        {
            return;
        }
        cout << no << ". [" << akar->kode << "]" << akar->nama << endl;
        no++;
        preorder(akar->kiri, no);
        preorder(akar->kanan, no);
    }

    void inorder(nodeTree * akar, int &no)
    {
        if (akar == NULL)
        {
            return;
        }
        inorder(akar->kiri, no);
        cout << no << ". [" << akar->kode << "]" << akar->nama << endl;
        no++;
        inorder(akar->kanan, no);
    }

    void postorder(nodeTree * akar, int &no)
    {
        if (akar == NULL)
        {
            return;
        }
        postorder(akar->kiri, no);
        postorder(akar->kanan, no);
        cout << no << ". [" << akar->kode << "]" << akar->nama << endl;
        no++;
    }

    void tambah_energi()
    {
        int kode;
        string nama;
        cout << "Masukkan kode energi anda: ";
        cin >> kode;
        if (cin.fail() || nota <= 0)
        {
            cin clear();
            cin.ignore(1000, '\n');
            cout << "Nomor kode harus berupa angka lebih dari 0!" << endl
                 << endl;
            return;
        }
        nodeQueue *q = front;
        while (q != NULL)
        {
            if (q->kode == kode)
            {
                cout << "Nomor kode sudah digunakan!" << endl
                     << endl;
                return;
            }
            q = q->next;
        }
        nodeStack *s = top;
        while (s != NULL)
        {
            if (s->kode == kode)
            {
                cout << "Nomor kode sudah digunakan!" << endl
                     << endl;
                return;
            }
            s = s->next;
        }
        cout << "Masukkan nama energi: ";
        cin.ignore();
        getline(cin, nama);
        if (nama.empty())
        {
            cout << "Nama energi tidak boleh kosong!" << endl
                 << endl;
            return;
        }
        nodeQueue *nb = new nodeQueue{kode, nama, NULL};
        if (front == NULL)
        {
            front = last = nb;
        }
        else
        {
            last->next = nb;
            last = nb;
        }
        cout << "Berhasil memasukkan energi!" << endl
             << endl;
    }

    void lihat_antrean()
    {
        IF(front == NULL)
        {
            cout << "Antrean energi masih kosong!" << endl
                 << endl;
            return;
        }
        cout << "==== Energi Dalam Antrean ====" << endl
             << endl;
        nodeQueue *nb = front;
        int no = 1;
        while (nb != NULL)
        {
            cout << no << ". [" << nb->kode << "]" << nb->nama << endl;
            nb = nb->next;
            no++;
        }
        cout << endl;
    }

    void proses_energi()
    {
        if (front == NULL)
        {
            cout << "Antran energi masih kosong!" << endl
                 << endl;
            return;
        }
        nodeQueue *hapus = front;
        nodeStack *nb = new nodeStack{hapus->kode, hapus->nama, top};
        top = nb;
        root = tambah_tree(root, hapus->kode, hapus->nama);
        cout << "Berhasil memproses energi" << hapus->nama << "!" << endl
             << endl;
        front = hapus->next;
        if (front == NULL)
        {
            last NULL;
        }
        delete hapus;
    }

    void lihat_energi()
    {
        if (top == NULL)
        {
            cout << "Belum ada energi yang sudah diresap!" << endl
                 << endl;
            return;
        }
        cout << "=== Energi yang Sudah Terserap ===" << endl
             << endl;
        nodeStack *nb = top;
        int no = 1;
        while (nb != NULL)
        {
            cout << no << ".[" << nb->kode << "]" << nb->nama << endl;
            nb = nb->next;
            no++;
        }
        cout << endl;
    }

    void cari_energi()
    {
        if (root == NULL)
        {
            cout << "Energi masih kosong!" << endl
                 << endl;
            return;
        }
        int kode;
        cout << "Masukkan nomor kode: ";
        cin >> kode;
        if (cin.fail() || kode <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Nomor kode harus berupa angka lebih dari 0!" << endl
                 << endl;
            return;
        }
        nodeTree *hasil = cari_tree(root, kode);
        if (hasil == NULL)
        {
            cout << "Energi dengan kode " << kode << " tidak ada!" << endl
                 << endl;
            return;
        }
        cout << "Ditemukan: [" << hasil->kode << "]" << hasil->nama << endl
             << endl;
    }

    void lihat_isiOrgan()
    {
        if (root == NULL)
        {
            cout << "masih kosong!" << endl
                 << endl;
            return;
        }
        char pil;
        int no = 1;
        cout << "=== Isi Organ ===" << endl
             << endl;
        cout << "1. Pre-Order" << endl;
        cout << "2. In-Order" << endl;
        cout << "3. Post-Order" << endl
             << endl;
        cout << "Masukkan pilihan anda: ";
        cin >> pil;
        cout << endl;
        switch (pil)
        {
        case '1':
        {
            preorder(root, no);
            break;
        }
        case '2':
        {
            inorder(root, no);
            break;
        }
        case '3':
        {
            postorder(root, no);
            break;
        }
            default
            {
                cout << "Pilihan yang anda masukkan salah!" << endl;
            }
        }
        cout << endl;
    }
}
