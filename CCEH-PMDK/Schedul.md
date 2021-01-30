# Schedule to move directory into DRAM


## Previouse implementation

Reference for Directory and data members in Directory.

``` c++
class CCEH : public Hash {
    private:
	    TOID(struct Directory) dir;
}

struct Directory{
    static const size_t kDefaultDepth = 10;

    TOID_ARRAY(TOID(struct Segment)) segment;	

    int64_t sema = 0;
    size_t capacity;		
    size_t depth;	

    bool suspend();
    bool lock();
    void unlock(void){

    void initDirectory(void)
    void initDirectory(size_t _depth)
}
```

The only update for informations in directory occures during splitting 1 and 2:
1. split operation 1: split a segment of local depth i to i+1 on the global depth equal to or greater than i+1 

CCEH::insert流程图：
``` flow
st=>start: start
op1=>operation: ***通过x哈希值以及当前的directory的global depth，获取segment index***
op2=>operation: ***访问directory存放的segment指针***
op3=>operation: 对segment进行访问控制和判断，获取segment的互斥锁
op4=>operation: 在segment中进行空闲位置查找和插入操作
op5=>operation: 未找到空闲位置，对segemt调用split，生成一个新的segment，并搬迁数据。
cond1=>operation: local depth和global depth相等，进行double resize
    op6=>operation: ***重新分配directory以及segment指针数组***
    op7=>operation: 进行segment数据搬迁
    op8=>operation: 刷写segment数据
    op9=>operation: ***刷写directory***
    op10=>operation: ***更新CCEH的directory指针***
    op11=>operation: 增加被分裂segment local depth并刷写
    op12=>operation: 释放对segment的互斥锁
cond2=>local dept小于global depth，进行一次正常split
    op13=>operation: ***按照MSB的segment index，更新directory的指针数据中所有共享segment 指针***
    op14=>operation: 增加被分裂segment local depth并刷写
    op15=>operation: 释放对segment的互斥锁
e=>end: end
st->op1->op2->op3->op4->op5->cond1
cond1(yes)->op6->op7->op8->op9->op10->op11->op12->e
cond1(no)->cond2
cond2(yes)->op13->op14->op15->e
cond2(no)->e
```
2. resize directory of global depth i to global depth i+1.
``` flow
    st=>start: start
    op1=>operation: ***更新directory共享segment指针部分***
    e=>end: end
    st->op1->e
```

Get操作流程图：
``` flow
    st=>start: start
    op1=>operation: ***通过x哈希值以及当前的directory的global depth，获取segment index***
    op2=>operation: ***访问directory存放的segment指针***
    op3=>operation: 对segment进行访问控制和判断，获取segment的互斥锁
    op4=>operation: 在segment中进行空闲位置查找和插入操作
    e=>end: end
    st->op1->op2->op3->op4->e
```

Recovery操作流程图：
``` flow
    st=>start: start
    op1=>operation: ***访问directory的global depth g和其中的每个一个segment指针***
    op2=>operation: 对每一个segmet x的local depth i，对后续2^(g-i)的segment进行判断
    cond1=>condition: ***如果后续segment y的local depth不为i，
    op3=>operation: 更新directory指针数组中y的指针指向x***
    e=>end: end
    st->op1->op2->cond1
    cond1(yes)->op3->e
    cond1(no)->e
```

## Transplant

### Version 1.0

Transplant single-thread , in-place and no-placement policy(linear probe or cuckoo placement) version

* directory





