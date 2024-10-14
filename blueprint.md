# lab 1 - Blueprint

## Interpreation

1. load csv(s) design data structure
   1. 基于字典，索引-企业信息-专利**链表**
   2. 双字典？企业-专利-多个企业？（是不是不太可能）
2. 操作
   1. 增加元素（专利申请）
   2. 专利授权？
   3. 插入、删除元素（专利转让）
3. CLI界面
   1. 输入边界
   2. 简单交互，清屏

读取的时候，每读一个就把patent加入到对应firm_id的企业中；所以还是用链表

用链表和栈实现

# 根据DSACPP 手动实现各种模板类