package main

/*
	定义节点，以及节点的操作
*/
//用 bool 类型定义节点的颜色
const (
	RED   bool = true
	BLACK bool = false
)

type Key int   //定义键
type Value int //定义值

type Node struct {
	key   Key   //键
	val   Value //值
	left  *Node //左子树
	right *Node //右子树
	count int   //以该节点为根节点的子树中的节点总数，先定义了，但不使用
	color bool  //节点的颜色，也是其父节点指向它的链接的颜色
}

func NewNode(key Key, val Value, count int, color bool) *Node {
	return &Node{key: key, val: val, count: count, color: color}
}

//判断节点是否是红色
func isRed(n *Node) bool {
	if n == nil {
		return false
	}
	return n.color == RED
}

//左旋转
func rotateLeft(n *Node) *Node {
	/*
		传进来的 n 节点是父节点，其右子节点 x 是红色节点
		现在要将 x 节点提上来作为新的父节点。 n 节点要变成红色，并成为 x 的左子节点，
		x 原来的左子节点转移到 n 的右子节点上
		然后将新的父节点 x 返回
	*/
	x := n.right
	n.right = x.left
	x.left = n

	x.color = n.color //继承父节点的颜色
	n.color = RED     //n节点变成红色

	return x
}

//右旋转
func rotateRight(n *Node) *Node {
	/*
		传进来的 n 节点是父节点，其左子节点 x 是红色节点
		现在要将 x 节点提上来作为新的父节点。 n 节点要变成红色，并成为 x 的右子节点，
		x 原来的右子节点转移到 n 的左子节点上
		然后将新的父节点 x 返回
	*/
	x := n.left
	n.left = x.right
	x.right = n

	x.color = n.color //继承父节点的颜色
	n.color = RED     //n节点变成红色

	return x
}

//颜色转换
func filpColors(n *Node) {
	/*
		n 节点作为父节点，其左右子节点都是红色的，
		现在要将左右子节点的颜色都变成黑色，将 n 节点变成红色
	*/
	n.color = RED
	n.left.color = BLACK
	n.right.color = RED
}

/*
	下面我们定义红黑树以及方法
*/

type redBlackTree struct {
	root *Node //根节点
}

//查，根据 key 得到 value
func (r *redBlackTree) Get(key Key) (Value, bool) {
	//以根节点为开始，递归找
	return r.get(r.root, key)
}

func (r *redBlackTree) get(n *Node, key Key) (Value, bool) {
	if n == nil {
		return -1, false
	}

	if n.key > key {
		return r.get(n.left, key)
	} else if n.key < key {
		return r.get(n.right, key)
	}

	return n.val, true
}

/*
	插入节点
	插入操作，需要先在树的底部找到插入的位置，然后从下到上处理红节点，递归最合适
*/
func (r *redBlackTree) Put(key Key, val Value) {
	//root 节点在递归中可能会改变，新的 root 节点会从递归中返回
	r.root = r.put(r.root, key, val)
	//根节点始终为黑色
	r.root.color = BLACK
}

func (r *redBlackTree) put(n *Node, key Key, val Value) *Node {
	//从根节点开始朝下找
	if n == nil {
		/*
			找到了空节点，说明该 key 在树上不存在。
			新建一个节点。初始为红色，将这个节点返回给其父节点，挂到父节点下面
		*/
		return NewNode(key, val, 1, RED)
	}

	if n.key > key {
		//向左边找。
		//因为我们在下面会处理红节点，所以 n 的左子节点经过旋转等操作后可能会变
		//处理完以后 n 的左子节点会从递归中返回，n 要接一下
		n.left = r.put(n.left, key, val)
	} else if n.key < key {
		//向右边找。
		//因为我们在下面会处理红节点，所以 n 的右子节点经过旋转等操作后可能会变
		//处理完以后 n 的右子节点会从递归中返回，n 要接一下
		n.right = r.put(n.right, key, val)
	} else {
		//找到了节点，直接赋值
		n.val = val
	}

	//将红色右节点变成红色左节点，但是不要把左右子节点都是红色的情况破坏了
	if isRed(n.right) && !isRed(n.left) {
		n = rotateLeft(n)
	}

	//处理两个连续红色左子节点
	if isRed(n.left) && isRed(n.left.left) {
		n = rotateRight(n)
	}

	//颜色转换
	if isRed(n.left) && isRed(n.right) {
		filpColors(n)
	}
	return n
}


func main() {

}
