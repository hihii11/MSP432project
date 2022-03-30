import os
import tkinter as tk
from tkinter import scrolledtext
from tkinter import ttk
import win32ui
import shutil
from shutil import copy
from tkinter import filedialog

dir_txt=os.listdir("D:\CCS\MSP432project")
Demo_lsit = []
file_list = []

top=tk.Tk()#创建消息循环
top.title('PID_assistant-1.0')
top.geometry("380x320")
def go(*args):
    return  0
def find_demo(dir_txt):
    Demo_dir = []
    for dir in dir_txt:
        index = 0
        for txt in dir:
            if txt != ".":
                index = index +1
                break
        if((dir[index+1:index+5] == "Exin") | (dir[index+1:index+5] == ".Exi")):
            Demo_dir.append(dir+"/exinlibs")
    return Demo_dir

def find_demo_list():
    global Demo_lsit
    Demo_lsit = find_demo(dir_txt)
    show_txt = "find list:\n"
    screen.delete('1.0', 'end')
    Bin1_txt ="All\n"
    for txt in Demo_lsit:
        show_txt = show_txt + txt +"\n"
        Bin1_txt = Bin1_txt + txt +"\n"
    #screen.delete('1.0', 'end')
    screen.insert('end',show_txt)
    screen.see('end')
    Bin1["values"] = Bin1_txt

def add_deal_files():
    dlg = win32ui.CreateFileDialog(1)
    dlg.SetOFNInitialDir(__file__)
    dlg.DoModal()
    filename = dlg.GetPathName()
    file_list.append(filename)
    screen.insert('end', "now deal file:\n")
    i = 0
    for txt in file_list:
        if (txt != ''):
            i = i + 1
        screen.insert('end', txt +"\n")
    screen.insert('end', "file number:"+str(i)+"\n")
    screen.insert('end', "\n")
    screen.see('end')

def clr_deal_files():
    global file_list
    file_list=[]
    screen.insert('end', "now deal file:\n")
    i = 0
    for txt in file_list:
        if (txt != ''):
            i = i + 1
        screen.insert('end', txt + "\n")
    screen.insert('end', "file number:" + str(i) + "\n")
    screen.insert('end', "\n")
    screen.see('end')

def deal_files():
    copy_num = 0
    cover_num = 0
    delete_num = 0
    add_num = 0
    deal_list = []
    deal_file = []
    if e1.get() == "All":
        deal_list = Demo_lsit
    else:
        deal_list.append(e1.get()+'\\'+'exinlibs')
    deal_file = file_list

    if e2.get() == 'Copy':
        for dir in deal_list:
            for file in deal_file:
                if(file!=''):
                    txt = "copy file.Source Path:"+file + "\n         Destination Path:"+dir+'\n'
                    screen.insert('end', txt)
                    screen.see('end')
                    copy_num = copy_num+1
                    try:
                    #print(file,os.path.dirname(__file__))
                        copy(file,dir)
                    except:
                        print('1')
    elif e2.get() == 'Delete':
        global root,var,entry1

        def conver():
            global delete_file_name, root, var, entry1
            delete_file_name = entry1.get()
            print(delete_file_name)
            root.destroy()
            root.quit()

        root = tk.Tk(className='file delete')  # 弹出框框名
        root.geometry('270x60')  # 设置弹出框的大小 w x h

        var = tk.StringVar(value="input file name")  # 这即是输入框中的内
        entry1 = tk.Entry(root, textvariable=var)  # 设置"文本变量"为var
        entry1.pack()  # 将entry"打上去"
        conver = tk.Button(root, text='确定', font=('Arial', 10), width=12, height=1, command=conver,
                       borderwidth=5, relief="groove")
        conver.pack()
        root.mainloop()
        print(deal_list)
        for dir in deal_list:
            global  delete_file_name
            txt = "delete file.File name:" + delete_file_name + "\n         Destination Path:" + dir + '\n'
            screen.insert('end', txt)
            screen.see('end')
            try:
                os.remove(dir+'\\' + delete_file_name)
            except:
                print(0)
            delete_num = delete_num +1
    txt = "total copy:" + str(copy_num) + "         total delete:" + str(delete_num) + '\n'
    screen.insert('end', txt)
    screen.see('end')


b0=tk.Button(top,text='寻找例程模板',font=('Arial',10),width=12,height=1,command= find_demo_list,borderwidth=5,relief="groove")
b0.place(x=10, y=10)
tk.Label(top,text='操作路径:',font=('Arial',11),width=8,justify=tk.LEFT,
         height=1,
         borderwidth=1,
         relief="groove"
         ).place(x=140, y=15)
e1 = tk.StringVar(value='All')
Bin1 = ttk.Combobox(textvariable=e1, width=15)
Bin1["values"] = ('All')
Bin1.current(0)
Bin1.bind("<<Binselect>>", go)
Bin1.place(x=220, y=15)

b1=tk.Button(top,text='添加操作文件',font=('Arial',10),width=12,height=1,command= add_deal_files
,borderwidth=5,relief="groove")
b1.place(x=10, y=50)

b2=tk.Button(top,text='清空操作文件',font=('Arial',10),width=12,height=1,command= clr_deal_files
,borderwidth=5,relief="groove")
b2.place(x=140, y=50)

b3=tk.Button(top,text='处理',font=('Arial',10),width=9,height=1,command= deal_files
,borderwidth=5,relief="groove")
b3.place(x=20, y=90)

tk.Label(top,text='操作类型:',font=('Arial',11),width=8,justify=tk.LEFT,
         height=1,
         borderwidth=1,
         relief="groove"
         ).place(x=140, y=90)

e2 = tk.StringVar(value='Copy')
Bin2 = ttk.Combobox(textvariable=e2, width=15)
Bin2["values"] = ('Copy','Delete')
Bin2.current(0)
Bin2.bind("<<Binselect>>", go)
Bin2.place(x=220, y=90)

screen = scrolledtext.ScrolledText(top, width=48, height=12)  # 38 20
screen.place(x=10, y=130)

top.mainloop()
