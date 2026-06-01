#pragma once
#include "afxdialogex.h"
#include "Karyawan.h"

class CKaryawanMFCDlg : public CDialogEx {
    DECLARE_DYNAMIC(CKaryawanMFCDlg)

public:
    CKaryawanMFCDlg(CWnd* pParent = nullptr);
    virtual ~CKaryawanMFCDlg();
    enum { IDD = IDD_KARYAWANMFC_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

private:
    LinkedList db;
    string selectedID;

    // ANGGOTA 3 - Fungsi tampilan daftar karyawan
    void RefreshList();
    void ClearForm();
    void LoadToForm(Node* node);

public:
    // ANGGOTA 1 - Tombol tambah data karyawan
    afx_msg void OnBnClickedBtnTambah();

    // ANGGOTA 2 - Tombol pencarian dan hapus data
    afx_msg void OnBnClickedBtnCari();
    afx_msg void OnBnClickedBtnHapus();

    // ANGGOTA 3 - Tombol edit, slip gaji, reset tampilan
    afx_msg void OnBnClickedBtnEdit();
    afx_msg void OnBnClickedBtnGaji();
    afx_msg void OnBnClickedBtnReset();

    // ANGGOTA 3 - Klik baris tabel untuk load data ke form
    afx_msg void OnNMClickList(NMHDR* pNMHDR, LRESULT* pResult);

    // Kontrol GUI (DDX) 
    CEdit     m_edtNama;
    CEdit     m_edtJabatan;
    CEdit     m_edtDivisi;
    CEdit     m_edtGaji;
    CComboBox m_cmbStatus;
    CEdit     m_edtCari;
    CListCtrl m_listKaryawan;
    CStatic   m_lblID;
};