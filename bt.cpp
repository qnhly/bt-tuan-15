//Mục lục của một cuốn sách được lưu trữ dưới dạng một cây trong đó mỗi node có thể là chapter, section, subsection, subsubsection.  
//Khai báo cấu trúc cây để biểu diễn cuốn sách. Các thông tin chứa ở mỗi node sinh viên tự đưa vào để đảm bảo các nội dung sau được thực hiện:  
#include <iostream>
using namespace std;

struct Nodechapter{
    string title;   //ten chuong
    int pages;      //so trang

    Nodechapter *left;
    Nodechapter *right;
    //khoi tao
    Nodechapter( string name, int val){
        title = name;
        pages = val;
        left = nullptr;
        right = nullptr;
    }
};
//ham ktra sach rong
bool isEmpty(Nodechapter *t){
    return t==nullptr;
}
//Xác định số chương của cuốn sách
void countChapters (Nodechapter *root, int &count){
    if(isEmpty(root)) return;
    count++;
    countChapters(root->left, count);
    countChapters(root->right,count);
}
//Tìm chương dài nhất của cuốn sách 
Nodechapter* findlongest(Nodechapter *root, Nodechapter* &longest){
    if (isEmpty(root))  return longest; //Tham chiếu đảm bảo rằng con trỏ longest truyền vào hàm có thể được thay đổi và cập nhật trực tiếp bên ngoài hàm.
    if (longest == nullptr || root->pages > longest->pages){
        longest = root;
    }
    findlongest(root->left,longest);
    findlongest(root->right,longest);
    return longest;
}
//Thực hiện tìm một mục và xoá mục đó khỏi sách. Lưu ý cập nhật lại số trang của từng mục.
Nodechapter* deleteChapter(Nodechapter *root, const string &title){
    if(isEmpty(root)) return nullptr;
    //tim node can xoa
    if(root->title == title){
        //neu node chi co 1 con OR 0 con
        if(isEmpty(root->left)){
            Nodechapter *temp = root->right;
            delete root;
            return temp;
        }else if(isEmpty(root->right)){
            Nodechapter *temp= root->left;
            delete root;
            return temp;
        }
        //neu node co 2 con
        Nodechapter *temp = root->right;  //tim node nho nhat trong cay con phai
        while(temp && temp->left != nullptr){
            temp = temp->left;
        }
        root->title = temp->title;  //sao chep gtri
        root->pages = temp->pages;  //cap nhat so trang
        root->right = deleteChapter(root->right, temp->title);  //xoa node nho nhat
    }else if (title < root->title){
        root->left = deleteChapter(root->left, title);
    }else{
        root->right = deleteChapter(root->right, title);
    }
    return root;
}