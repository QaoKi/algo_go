package main

import (
	"math/rand"
	"time"
)

/*
	������Ĳ���ʱ�临�Ӷ�Ϊ O(n)����������ڵ������Ϲ��������㣬���ö��ֲ��ҵ�˼�������ټ������ݡ�
	������ҵ�ʱ�临�Ӷȣ�O(logn)���Ͷ��ֲ�����ͬ��
	����Ŀռ����ģ�O(n)
*/
/*
	��Ŀ��leetcode 1206
		��ʹ���κο⺯�������һ������
		�������� O(log(n)) ʱ����������ӡ�ɾ�����������������ݽṹ��
		����������������������书���������൱����������Ĵ��볤������¸��̣������˼�����������ơ�

		�������кܶ�㣬ÿһ����һ���̵�����
		�ڵ�һ��������£����ӡ�ɾ��������������ʱ�临�ӶȲ����� O(n)��
		�����ÿһ��������ƽ��ʱ�临�Ӷ��� O(log(n))���ռ临�Ӷ��� O(n)��

		�ڱ����У�������Ӧ��Ҫ������Щ������
			bool search(int target) : ����target�Ƿ�����������С�
			void add(int num): ����һ��Ԫ�ص�����
			bool erase(int num): ��������ɾ��һ��ֵ����� num �����ڣ�ֱ�ӷ���false.
								������ڶ�� num ��ɾ����������һ�����ɡ�

		ע�⣬�����п��ܴ��ڶ����ͬ��ֵ����Ĵ�����Ҫ�������������
*/

const (
	maxLevel   = 16 // ���㼶
	p          = 0.25
	ERROR_CODE = -43962200
)

type Skiplist struct {
	head  *node // ͷ�ڵ㣬ÿһ�㶼��ͷ�ڵ㣬�� head �ڵ��е� len(next) ���� level
	level int   // ��ǰ�������ж��ٲ�
}

type node struct {
	key   int     // ÿ��ĵ������ǰ��� key �������
	value int     // key ��Ӧ�� value ֵ���� zset �У��������� key��
	next  []*node // ָ����һ���ڵ��ָ�룬����һ�����飬��Ϊһ���ڵ���ܳ����ڶ���㼶��
}

func newNode(key, value int, level int) *node {
	return &node{
		key:   key,
		value: value,
		next:  make([]*node, level),
	}
}

// ��ȡ���level
func randomLevel() int {
	level := 1
	for level < maxLevel && rands() < p {
		level++
	}
	return level
}

func rands() float32 {
	rand.Seed(time.Now().UnixNano())
	return rand.Float32()
}

func Constructor() Skiplist {
	return Skiplist{
		head: &node{
			// ֱ���� head ����ߵȼ�����������Ĳ㼶û�����ݣ���ô head ָ�� nil ����
			next: make([]*node, maxLevel),
		},
	}
}

func (this *Skiplist) Search(target int) bool {
	_, succ := this.search(target)
	return succ
}

func (this *Skiplist) search(target int) (*node, bool) {
	// ����߲㿪ʼ���������ң��������£�ֱ��������ײ�
	c := this.head
	for level := this.level - 1; level >= 0; level-- {
		// ��ÿһ���г������ұ�����ֱ����һ���ڵ㲻���ڻ��߽ڵ�� key ֵ���ڵ��� target
		for c.next[level] != nil && c.next[level].key < target {
			// ��ǰ�ڵ�����һ��ֱ����ǰ
			c = c.next[level]
		}
		// �����ǰ�ڵ����һ���ڵ㲻Ϊ�գ����� key ֵ���� target�����ҵ���
		// ���������һ����
		if c.next[level] != nil && c.next[level].key == target {
			return c.next[level], true
		}
	}
	// �ҵ�������һ�㻹û���ҵ���˵��Ԫ�ز����ڡ�
	return nil, false
}

func (this *Skiplist) Add(key int) {
	// ������˵valueӦ���Ǵ�������, ��Add(key, value int)
	// ���� leetcode ��û���õ� value �ֶΣ������Ĭ�� value Ϊ 1
	value := 1
	/*
		// �� search һ�����key�治���ڣ�������ڣ�ֱ�Ӹ��� value ����
		// ��������������ظ���key, ��������ע�͵�

		if node, succ := this.search(key); succ {
			node.value = value
			return
		}
	*/

	c := this.head
	// update������¼ÿһ�����һ��С�� key �Ľڵ㣬���ͳһ�������ӹ�ϵ
	update := make([]*node, maxLevel)
	for level := this.level - 1; level >= 0; level-- {
		// ����߲㿪ʼ��ÿһ�㶼���ұ������ҵ�ÿһ�����һ��С�� key �Ľڵ�
		for c.next[level] != nil && c.next[level].key < key {
			c = c.next[level]
		}
		// ��¼��
		update[level] = c
	}

	// ���һ���㼶
	rdmlevel := randomLevel()
	// ����������level�ȵ�ǰ��levelҪ��, ��ǰ��߲㼶Ҫ���£�
	// ����ͷ�ڵ�� next ָ��ҲҪ����
	if rdmlevel > this.level {
		for level := this.level; level < rdmlevel; level++ {
			update[level] = this.head
		}
		this.level = rdmlevel
	}
	e := newNode(key, value, rdmlevel)
	// ����ÿһ������
	// o->last => o->update->last
	for level := 0; level < rdmlevel; level++ {
		e.next[level] = update[level].next[level]
		update[level].next[level] = e
	}
}

func (this *Skiplist) Erase(target int) bool {
	// �� search һ��key����target�Ľڵ�治���ڣ������ڣ�ֱ�ӷ���
	if _, succ := this.search(target); !succ {
		return false
	}

	c := this.head
	update := make([]*node, maxLevel)
	for level := this.level - 1; level >= 0; level-- {
		// ����߲㿪ʼ��ÿһ�㶼���ұ������ҵ�ÿһ����� target �Ľڵ��ǰһ���ڵ�
		for c.next[level] != nil && c.next[level].key < target {
			c = c.next[level]
		}
		update[level] = c
	}
	// ��ʱ c.next[0] ָ�����������һ�㣬key���� target �Ľڵ㣬��Ҫ��ɾ����Ԫ��
	c = c.next[0]
	if c == nil || c.key != target {
		return false
	}

	// ����ÿһ������
	for level := 0; level < this.level; level++ {
		// o->update->last => o->last
		if update[level].next[level] != c {
			break
		}
		update[level].next[level] = c.next[level]
	}

	// ���²㼶 level
	for this.level > 1 && this.head.next[this.level-1] == nil {
		this.level--
	}
	return true

}

func main() {

}
