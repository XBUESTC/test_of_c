from math import log
import operator
import pandas as pd

#根据输入数据统计标签
def count_labels(data_set):
    labels_dic={}
    for i in data_set:
        if(i[-1] not in labels_dic.keys()):
            labels_dic[i[-1]]=0
        labels_dic[i[-1]]+=1
    return labels_dic

def Create_dataset():

    #读取excel中的文件数据
    file_name=r"C:\Users\16236\Desktop\data1.xlsx"
    raw_data=pd.read_excel(file_name)
    raw_data=raw_data.values
    print(raw_data)


    for i in raw_data:
        if(len(i[-1])!=1):
            i[-1]=i[-1][0]


    labels=['核心体温','体表温度','血氧饱和度','血压水平','出院决定']
    return raw_data,labels
#指定标签进行数据划分
#输入数据集,横坐标，值
def Sec_dataset(data_set,axis,value):
    data_set_new=[]
    for i in data_set:
        if(i[axis]==value):
            data_set_new.append(i)
    return data_set_new


#计算指定数据的信息熵
def Calc_ShannonEnt(data_set):
    labels_count=count_labels(data_set)
    data_len=len(data_set)  #样本个数
    shannonEnt=0.0
    for i in labels_count.keys():
        prob=float (labels_count[i])/data_len
        shannonEnt-=prob*log(prob)
    return shannonEnt


#计算指定属性的期望值
def Calc_p(data_set,axis):

    #先统计再该数据集中标签种类  以及数量
    elm_count={}
    for i in data_set:
        if i[axis] not in labels:
            elm_count[i[axis]]=0
        elm_count[i[axis]]+=1

    #存储期望
    list_qw=[]
    #计算期望
    #先将数据进行划分,然后在依次按公式求值然后求和
    #按标签依次计算期望  求和为最终的期望
    k=0
    for i in elm_count.keys():
        labels_other= {}
        data_new=Sec_dataset(data_set,axis,i)

        qw=0.0
        #统计各属性下标签类型
        labels_other=count_labels(data_new)

        #计算单独的期望值
        for j in labels_other.keys():
            pro=float(labels_other[j])/len(data_new)
            qw-=pro*log(pro)

        list_qw.append(qw*len(data_new)/len(data_set))
    return sum(list_qw)



#找到最适合分类的属性
def Find_best_axis(data_set,axis_mem):
    axis=0
    #计算信息熵
    w=Calc_ShannonEnt(data_set)

    list_qw=[]
    #计算期望信息熵
    for i in range(0,len(data_set[0])-1):
        list_qw.append(Calc_p(data_set,i))

    #计算信息增益并找到最大信息增益所在位置
    list_z=[]
    for i in range(0,len(list_qw)):
        if(i in axis_mem):           #增益为0说明该属性已经或者正在被分类
            list_z.append(0)
            continue
        list_z.append(w-list_qw[i])

    v=0
    pos = 0
    for i in range(0,len(list_z)):
       if v<list_z[i]:
            v=list_z[i]
            pos=i
    # print(pos)
    print(list_z)
    #根据位置分列数据

    #统计指定位置类型

    axis_count={}
    for i in data_set:
        if(i[pos] not in axis_count):
            axis_count[i[pos]]=0
        axis_count[i[pos]]+=1
    #划分数据
    #并返回划分数据
    result={}
    for i in axis_count.keys():
        result[i]=Sec_dataset(data_set,pos,i)

    return [pos,result]       #返回划分数据所用数据的坐标  以及 划分好的数据




def create_tree(data_set,labels_mem,labels):
    data_mem={}
    labels_types=count_labels(data_set)

    if len(labels_types)==1:
        return data_set[0][-1]

    if len(labels_mem)==len(labels):
        return  data_set[0][-1]

    #出现了同种 label_type种类相同的情况

    axis_mem=[]
    for i in range(0,len(labels)):
        if(labels[i] in labels_mem):
            axis_mem.append(i)

    [axis_max,data_new]=Find_best_axis(data_set,axis_mem)
    best_label=labels[axis_max]
    labels_mem.append(best_label)

    tree = {best_label:{}}


    for i in data_new.keys():
        subLabels = labels_mem[:]
        tree[best_label][i]=create_tree(data_new[i],subLabels,labels)

    return tree




[data_set,labels]=Create_dataset()
label_mem=[]

featlabels=[]
[bestFeat,data_new]=Find_best_axis(data_set,[])

tree=create_tree(data_set,label_mem,labels)
print("树")
print(tree)

