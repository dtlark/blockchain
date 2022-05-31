package blockchain

//"github.com/dtlark/blockchain/db"
import (
	"fmt"

	"github.com/syndtr/goleveldb/leveldb"
)

const (
	databasePath = "./tmp/blocks"
)

type BlockChain struct {
	EndBlockHash []byte
	Db           *leveldb.DB //Low level persistent database to store final content in
}

type BlockChainIterator struct {
	CurrHash []byte
	Db       *leveldb.DB
}

func Genesis() *Block {
	return CreateBlock("In the beginning...", []byte{})
}

func (chain *BlockChain) AddBlock(data string) {
	var endBlockHash []byte

	//get end block hash
	hash, _ := chain.Db.Get([]byte("end"), nil)
	endBlockHash = hash

	new := CreateBlock(data, endBlockHash)

	err := chain.Db.Put([]byte("end"), new.Hash, nil)
	check("Assigning new block to end", err)

	chain.EndBlockHash = new.Hash

}

func InitBlockChain() *BlockChain {

	var endBlockHash []byte

	db, err := leveldb.OpenFile(databasePath, nil)
	check("leveldb open fail", err)

	_, err = db.Get([]byte("end"), nil)
	if err == leveldb.ErrNotFound {
		fmt.Println("No blockchain found. Creating...")
		genesis := Genesis()

		err = db.Put(genesis.Hash, genesis.Encode(), nil)
		check("Put genesis", err)
		err = db.Put([]byte("end"), genesis.Hash, nil)
		check("Put end", err)

		endBlockHash = genesis.Hash
	} else {

		data, _ := db.Get([]byte("end"), nil)
		endBlockHash = data
	}

	bc := BlockChain{endBlockHash, db}
	return &bc
}

func (chain *BlockChain) Iterator() *BlockChainIterator {
	iter := &BlockChainIterator{chain.EndBlockHash, chain.Db}

	return iter
}

func (iter *BlockChainIterator) Next() *Block {
	var block *Block

	data, err := iter.Db.Get(iter.CurrHash, nil)
	check("Get data from CurrHash", err)
	block = Decode(data)

	iter.CurrHash = block.PrevHash

	return block
}
