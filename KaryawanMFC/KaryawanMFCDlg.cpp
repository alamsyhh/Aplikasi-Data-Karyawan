#include "pch.h"
#include "KaryawanMFC.h"
#include "KaryawanMFCDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include <iomanip>

IMPLEMENT_DYNAMIC(CKaryawanMFCDlg, CDialogEx)

CKaryawanMFCDlg::CKaryawanMFCDlg(CWnd* pParent)
    : CDialogEx(IDD_KARYAWANMFC_DIALOG, pParent), selectedID("") {
}

CKaryawanMFCDlg::~CKaryawanMFCDlg() {}

void CKaryawanMFCDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_NAMA, m_edtNama);
    DDX_Control(pDX, IDC_EDIT_JABATAN, m_edtJabatan);
    DDX_Control(pDX, IDC_EDIT_DIVISI, m_edtDivisi);
    DDX_Control(pDX, IDC_EDIT_GAJI, m_edtGaji);
    DDX_Control(pDX, IDC_CMB_STATUS, m_cmbStatus);
    DDX_Control(pDX, IDC_EDIT_CARI, m_edtCari);
    DDX_Control(pDX, IDC_LIST_KARYAWAN, m_listKaryawan);
    DDX_Control(pDX, IDC_LBL_ID, m_lblID);
}

BEGIN_MESSAGE_MAP(CKaryawanMFCDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_TAMBAH, &CKaryawanMFCDlg::OnBnClickedBtnTambah)
    ON_BN_CLICKED(IDC_BTN_EDIT, &CKaryawanMFCDlg::OnBnClickedBtnEdit)
    ON_BN_CLICKED(IDC_BTN_HAPUS, &CKaryawanMFCDlg::OnBnClickedBtnHapus)
    ON_BN_CLICKED(IDC_BTN_CARI, &CKaryawanMFCDlg::OnBnClickedBtnCari)
    ON_BN_CLICKED(IDC_BTN_RESET, &CKaryawanMFCDlg::OnBnClickedBtnReset)
    ON_BN_CLICKED(IDC_BTN_GAJI, &CKaryawanMFCDlg::OnBnClickedBtnGaji)
    ON_NOTIFY(NM_CLICK, IDC_LIST_KARYAWAN, &CKaryawanMFCDlg::OnNMClickList)
END_MESSAGE_MAP()

static string CStr2Str(CString cs) {
    CT2CA conv(cs); return string(conv);
}
static CString Str2CStr(const string& s) {
    return CString(s.c_str());
}

BOOL CKaryawanMFCDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    m_listKaryawan.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    m_listKaryawan.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 70);
    m_listKaryawan.InsertColumn(1, _T("Nama"), LVCFMT_LEFT, 140);
    m_listKaryawan.InsertColumn(2, _T("Jabatan"), LVCFMT_LEFT, 110);
    m_listKaryawan.InsertColumn(3, _T("Divisi"), LVCFMT_LEFT, 100);
    m_listKaryawan.InsertColumn(4, _T("Gaji Pokok"), LVCFMT_RIGHT, 110);
    m_listKaryawan.InsertColumn(5, _T("Status"), LVCFMT_LEFT, 80);

    m_cmbStatus.AddString(_T("Aktif"));
    m_cmbStatus.AddString(_T("Tidak Aktif"));
    m_cmbStatus.SetCurSel(0);

    m_lblID.SetWindowText(_T("ID: (otomatis)"));
    return TRUE;
}

void CKaryawanMFCDlg::RefreshList() {
    m_listKaryawan.DeleteAllItems();
    Node* temp = db.head;
    int   i = 0;
    while (temp) {
        ostringstream oss;
        oss << "Rp " << fixed << setprecision(0) << temp->data.gajiPokok;

        m_listKaryawan.InsertItem(i, Str2CStr(temp->data.id));
        m_listKaryawan.SetItemText(i, 1, Str2CStr(temp->data.nama));
        m_listKaryawan.SetItemText(i, 2, Str2CStr(temp->data.jabatan));
        m_listKaryawan.SetItemText(i, 3, Str2CStr(temp->data.divisi));
        m_listKaryawan.SetItemText(i, 4, Str2CStr(oss.str()));
        m_listKaryawan.SetItemText(i, 5, Str2CStr(temp->data.status));
        i++;
        temp = temp->next;
    }
}

void CKaryawanMFCDlg::ClearForm() {
    m_edtNama.SetWindowText(_T(""));
    m_edtJabatan.SetWindowText(_T(""));
    m_edtDivisi.SetWindowText(_T(""));
    m_edtGaji.SetWindowText(_T(""));
    m_cmbStatus.SetCurSel(0);
    m_lblID.SetWindowText(_T("ID: (otomatis)"));
    selectedID = "";
}

void CKaryawanMFCDlg::LoadToForm(Node* node) {
    m_edtNama.SetWindowText(Str2CStr(node->data.nama));
    m_edtJabatan.SetWindowText(Str2CStr(node->data.jabatan));
    m_edtDivisi.SetWindowText(Str2CStr(node->data.divisi));

    ostringstream oss;
    oss << fixed << setprecision(0) << node->data.gajiPokok;
    m_edtGaji.SetWindowText(Str2CStr(oss.str()));

    m_cmbStatus.SetCurSel(node->data.status == "Aktif" ? 0 : 1);
    m_lblID.SetWindowText(Str2CStr("ID: " + node->data.id));
    selectedID = node->data.id;
}

void CKaryawanMFCDlg::OnNMClickList(NMHDR* pNMHDR, LRESULT* pResult) {
    LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    int idx = pNMIA->iItem;
    if (idx < 0) return;

    CString id;
    m_listKaryawan.GetItemText(idx, 0, id.GetBuffer(20), 20);
    id.ReleaseBuffer();

    Node* node = db.cariByID(CStr2Str(id));
    if (node) LoadToForm(node);
    *pResult = 0;
}

void CKaryawanMFCDlg::OnBnClickedBtnTambah() {
    CString nama, jabatan, divisi, gaji;
    m_edtNama.GetWindowText(nama);
    m_edtJabatan.GetWindowText(jabatan);
    m_edtDivisi.GetWindowText(divisi);
    m_edtGaji.GetWindowText(gaji);

    if (nama.IsEmpty() || jabatan.IsEmpty() ||
        divisi.IsEmpty() || gaji.IsEmpty()) {
        MessageBox(_T("Semua field harus diisi!"),
            _T("Validasi"), MB_ICONWARNING);
        return;
    }

    Karyawan k;
    k.id = db.generateID();
    k.nama = CStr2Str(nama);
    k.jabatan = CStr2Str(jabatan);
    k.divisi = CStr2Str(divisi);
    k.gajiPokok = atof(CStr2Str(gaji).c_str());
    k.status = (m_cmbStatus.GetCurSel() == 0) ? "Aktif" : "Tidak Aktif";

    db.tambah(k);
    RefreshList();
    ClearForm();
    MessageBox(_T("Data karyawan berhasil ditambahkan!"),
        _T("Sukses"), MB_ICONINFORMATION);
}

void CKaryawanMFCDlg::OnBnClickedBtnCari() {
    CString keyword;
    m_edtCari.GetWindowText(keyword);

    if (keyword.IsEmpty()) {
        RefreshList();
        return;
    }

    string kw = CStr2Str(keyword);
    Node* hasil = db.cariByID(kw);
    if (!hasil)  hasil = db.cariByNama(kw);

    if (!hasil) {
        MessageBox(_T("Karyawan tidak ditemukan!"),
            _T("Info"), MB_ICONINFORMATION);
        return;
    }

    m_listKaryawan.DeleteAllItems();
    ostringstream oss;
    oss << "Rp " << fixed << setprecision(0) << hasil->data.gajiPokok;
    m_listKaryawan.InsertItem(0, Str2CStr(hasil->data.id));
    m_listKaryawan.SetItemText(0, 1, Str2CStr(hasil->data.nama));
    m_listKaryawan.SetItemText(0, 2, Str2CStr(hasil->data.jabatan));
    m_listKaryawan.SetItemText(0, 3, Str2CStr(hasil->data.divisi));
    m_listKaryawan.SetItemText(0, 4, Str2CStr(oss.str()));
    m_listKaryawan.SetItemText(0, 5, Str2CStr(hasil->data.status));
    LoadToForm(hasil);
}

void CKaryawanMFCDlg::OnBnClickedBtnHapus() {
    if (selectedID.empty()) {
        MessageBox(_T("Pilih karyawan dari tabel terlebih dahulu!"),
            _T("Info"), MB_ICONINFORMATION);
        return;
    }

    Node* node = db.cariByID(selectedID);
    CString konfirm;
    konfirm.Format(_T("Yakin hapus karyawan \"%s\"?"),
        Str2CStr(node->data.nama));

    if (MessageBox(konfirm, _T("Konfirmasi"),
        MB_YESNO | MB_ICONQUESTION) == IDYES) {
        db.hapus(selectedID);
        RefreshList();
        ClearForm();
        MessageBox(_T("Data karyawan berhasil dihapus!"),
            _T("Sukses"), MB_ICONINFORMATION);
    }
}

void CKaryawanMFCDlg::OnBnClickedBtnEdit() {
    if (selectedID.empty()) {
        MessageBox(_T("Pilih karyawan dari tabel terlebih dahulu!"),
            _T("Info"), MB_ICONINFORMATION);
        return;
    }

    Node* node = db.cariByID(selectedID);
    if (!node) return;

    CString nama, jabatan, divisi, gaji;
    m_edtNama.GetWindowText(nama);
    m_edtJabatan.GetWindowText(jabatan);
    m_edtDivisi.GetWindowText(divisi);
    m_edtGaji.GetWindowText(gaji);

    if (nama.IsEmpty() || jabatan.IsEmpty() ||
        divisi.IsEmpty() || gaji.IsEmpty()) {
        MessageBox(_T("Semua field harus diisi!"),
            _T("Validasi"), MB_ICONWARNING);
        return;
    }

    node->data.nama = CStr2Str(nama);
    node->data.jabatan = CStr2Str(jabatan);
    node->data.divisi = CStr2Str(divisi);
    node->data.gajiPokok = atof(CStr2Str(gaji).c_str());
    node->data.status = (m_cmbStatus.GetCurSel() == 0)
        ? "Aktif" : "Tidak Aktif";

    RefreshList();
    ClearForm();
    MessageBox(_T("Data karyawan berhasil diperbarui!"),
        _T("Sukses"), MB_ICONINFORMATION);
}

void CKaryawanMFCDlg::OnBnClickedBtnGaji() {
    if (selectedID.empty()) {
        MessageBox(_T("Pilih karyawan dari tabel terlebih dahulu!"),
            _T("Info"), MB_ICONINFORMATION);
        return;
    }

    Node* node = db.cariByID(selectedID);
    if (!node) return;

    double gaji = node->data.gajiPokok;
    double tunjangan = 0;
    if (node->data.jabatan == "Manager")    tunjangan = gaji * 0.20;
    else if (node->data.jabatan == "Supervisor") tunjangan = gaji * 0.15;
    else if (node->data.jabatan == "Staff")      tunjangan = gaji * 0.10;
    else                                         tunjangan = gaji * 0.05;

    double potongan = gaji * 0.02;
    double gajiBersih = gaji + tunjangan - potongan;

    ostringstream oss;
    oss << fixed << setprecision(0);
    oss << "========= SLIP GAJI =========\n";
    oss << "Nama          : " << node->data.nama << "\n";
    oss << "Jabatan       : " << node->data.jabatan << "\n";
    oss << "Divisi        : " << node->data.divisi << "\n";
    oss << "-----------------------------\n";
    oss << "Gaji Pokok    : Rp " << gaji << "\n";
    oss << "Tunjangan     : Rp " << tunjangan << "\n";
    oss << "Potongan BPJS : Rp " << potongan << "\n";
    oss << "-----------------------------\n";
    oss << "Gaji Bersih   : Rp " << gajiBersih << "\n";
    oss << "=============================\n";

    MessageBox(Str2CStr(oss.str()), _T("Slip Gaji"), MB_ICONINFORMATION);
}

void CKaryawanMFCDlg::OnBnClickedBtnReset() {
    m_edtCari.SetWindowText(_T(""));
    RefreshList();
    ClearForm();
}