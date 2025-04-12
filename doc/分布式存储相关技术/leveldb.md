leveldb详解

leveldb几乎是Bigtable的单机版实现，对分布式存储
运用
leveldb_open

# **背景**

项目源码地址：[https://github.com/google/leveldb](https://github.com/google/leveldb)

## **bigtable与leveldb的渊源**

    bigtableGoogle 在 2003、2004 以及 2006 年，分别抛出了三篇重磅论文。也就是我们常说的“大数据”的三驾马车：GFS、MapReduce 和 Bigtable
	LevelDB 是一个由 Google 开发的开源、高性能的键值存储库，专为快速读写操作而设计。它的历史和发展密切相关于 Google 的几项创新性技术，特别是 Bigtable 和 Google File System (GFS)。为了深入了解 LevelDB 的历史及其与这些技术的关系，需要先对 Bigtable 和 GFS 有基本的了解，然后探讨 LevelDB 的起源和它如何从这些技术中演化而来。

### Google File System (GFS)

    GFS 是 Google 开发的一种分布式文件系统，用于处理大量数据。它于2003年首次对外披露，旨在提供高吞吐量的大规模数据访问，同时保证数据的可靠性和容错能力。GFS 特别适用于大规模数据处理场景，比如搜索引擎和数据分析。GFS 的设计哲学极大地影响了后续的分布式存储系统的设计。

### Bigtable

    Bigtable，首次在2006年的一篇论文中被介绍，是一个分布式的、可扩展的数据存储系统，旨在处理海量数据。Bigtable 构建在 GFS 之上，利用 GFS 提供的底层数据存储能力，支持结构化数据的存储和查询。它能够动态地处理大量的数据，从而支持 Google 的各种产品，包括搜索、地图和 Gmail。

### Bigtable 与 GFS 的关系

    Bigtable 与 GFS 之间的关系是基于分层架构的。Bigtable 使用 GFS 作为其底层的文件存储系统，依赖 GFS 提供高效、可靠的数据存储能力。通过这种设计，Bigtable 可以专注于提供高效的数据索引和查询功能，而无需关心数据的物理存储细节。这种分层的设计方法使得 Bigtable 能够处理巨大规模的数据，同时保持高性能和高可用性。

### LevelDB 的起源

    LevelDB 的起源可以追溯到 Bigtable 的设计和实现。实际上，LevelDB 是由 Bigtable 的主要作者之一，Jeff Dean 和 Sanjay Ghemawat 在 Google 内部发起的项目。LevelDB 的设计目的是为了提供一个轻量级的、可嵌入的键值存储解决方案，它可以在本地环境中高效地处理数据存储和查询操作，而无需分布式系统的复杂性。

    LevelDB 直接受到 Bigtable 使用的 SSTable (Sorted Strings Table) 格式的启发。SSTable 是一种存储结构化数据的文件格式，用于在 Bigtable 中高效存储和查询数据。LevelDB 采用了类似的设计理念，并对其进行了简化和优化，以适应不同的使用场景。

### LevelDB 与 Bigtable 的关系

    LevelDB 与 Bigtable 的直接关系体现在它们共享相似的设计哲学和数据结构。虽然 LevelDB 是为本地存储场景设计的，而 Bigtable 则是为分布式环境设计的，但两者都采用了类似的 SSTable 数据结构和压缩算法，以及高效的数据索引和查询机制。LevelDB 的开发受益于 Bigtable 的经验和设计原则，可以被看作是 Bigtable 概念在单机环境下的应用。

    总之，LevelDB 的历史和发展紧密联系着 Google 的两项关键技术：GFS 和 Bigtable。通过从 Bigtable 和 GFS 的设计中汲取经验，LevelDB 成为了一种高效、可靠的本地存

储解决方案，广泛应用于各种需要高性能数据存储的应用中。

## 两类数据结构（B树类别和LSMT类别）

## **leveldb和LSMT**

①　LSMT（Log-Structured Merge-Tree）介绍

LSMT（Log-Structured Merge-Tree）是一种数据结构，用于高效地管理大量的写操作。它通过将所有的插入、更新和删除操作首先记录到一个内存中的数据结构（通常是一个排序的树，如红黑树或跳表），然后定期将这些操作批量合并到磁盘上的数据文件中，从而优化写操作的性能。这种设计使得LSMT特别适用于写密集型的应用场景。

LSMT的关键优势包括：

- **高效的写性能**：通过批量合并和写入操作，减少了磁盘I/O次数。
- **顺序写入**：将数据顺序地写入磁盘，减少了磁盘寻道时间，提高了写入效率。
- **可扩展性**：适合处理大规模数据集，因为数据是分批次、顺序写入的。
- **支持高效的范围查询**：由于数据在磁盘上是有序存储的，因此可以高效地支持范围查询操作。

②　LSM树与LevelDB的关系

在LevelDB中它使用了LSM树作为其核心数据结构，用于存储和管理键值对数据。在LevelDB中，所有的写入操作首先记录到一个内存中的日志文件（用于故障恢复），然后数据被存储在一个内存中的排序结构（如跳表）中，之后定期地将这些数据通过合并过程写入到磁盘上的SST（Sorted String Table）文件中。

LevelDB通过这种方式利用LSM树的优点，提供了高性能的写操作，同时还支持有效的读操作。由于LevelDB的设计，它特别适合用于需要高速写入和读取的场景，如移动应用、游戏和Web技术栈中的数据存储需求。

③　LevelDB中LSM树的实现（将在后文介绍）

# 二、**模块以及功能**

![](file:////private/var/folders/45/79bfk2bd5tl0h6xcxk3syrbw0000gn/T/com.kingsoft.wpsoffice.mac/wps-fengliyu/ksohtml//wps1.jpg)![1708155663386](image/leveldb/1708155663386.png "架构")

1）DB接口见

2）POSIX接口见

DBAPI：

dbopen

### Open db主体流程：

1. 初始化一个DBimpl实例
2. 加锁防止多线程重入
3. 识别是否有上一个掉电的db并且尝试从manifest和WAL中恢复
4. 尝试恢复之后的对象是否包含memtable，有说明存在掉电的数据则进入6，无则进入5
5. 创建新的Log和Memtable模块
6. 是否需要保存manifest文件，是进入7，否进入8
7. 将VersionEdit apply, 并落盘到Manifest中
8. 尝试删除无效文件，尝试compation
9. 解锁，给db指针赋值并且返回状态

```C++
leveldb_t* leveldb_open(const leveldb_options_t* options, const char* name,
                        char** errptr) {
  DB* db;
  if (SaveError(errptr, DB::Open(options->rep, std::string(name), &db))) {
    return nullptr;
  }
  leveldb_t* result = new leveldb_t;
  result->rep = db;
  return result;
}

Status DB::Open(const Options& options, const std::string& dbname, DB** dbptr) {
  *dbptr = nullptr;

  DBImpl* impl = new DBImpl(options, dbname);
  impl->mutex_.Lock();//加锁防止多线程open相同db
  VersionEdit edit;
  // Recover handles create_if_missing, error_if_exists
  bool save_manifest = false;
  Status s = impl->Recover(&edit, &save_manifest); // 从WAL中恢复memtable，其中会强制计算校验和避免恢复了错误的数据
  if (s.ok() && impl->mem_ == nullptr) {
    // 走这里说明不需要从日志里恢复，那么就要给impl实例创建一个新的memtable
    // Create new log and a corresponding memtable.
    uint64_t new_log_number = impl->versions_->NewFileNumber();
    WritableFile* lfile;
    s = options.env->NewWritableFile(LogFileName(dbname, new_log_number),
                                     &lfile);
    if (s.ok()) {
      edit.SetLogNumber(new_log_number);
      impl->logfile_ = lfile;
      impl->logfile_number_ = new_log_number;
      impl->log_ = new log::Writer(lfile);//生成新的log对象
      impl->mem_ = new MemTable(impl->internal_comparator_);//生成新的Memtable对象
      impl->mem_->Ref();// 引用计数被mutex保护住了引用计数所以直接加减
    }
  }
  if (s.ok() && save_manifest) {
    edit.SetPrevLogNumber(0);  // No older logs needed after recovery.
    edit.SetLogNumber(impl->logfile_number_);
    s = impl->versions_->LogAndApply(&edit, &impl->mutex_);
  }
  if (s.ok()) {
    impl->RemoveObsoleteFiles();// 尝试删除过期文件
    impl->MaybeScheduleCompaction();// 尝试compation
  }
  impl->mutex_.Unlock();//解锁
  if (s.ok()) {
    assert(impl->mem_ != nullptr);
    *dbptr = impl;
  } else {
    delete impl;
  }
  return s;
}
```

### Put/Write kv写接口主流程

1. 构建writer对象，并且插入writer队列
2. 是否有前面的写未完成，触发信号量等待
3. 预分配内存空间
4. 写WAL，即写Log
5. 更新MemTable
6. 更新SequenceNumber（其实也就是快照ID，所有的读写都带快照ID）
7. 执行完毕，发送信号通知队列上阻塞的写出队执行

```C++
void leveldb_put(leveldb_t* db, const leveldb_writeoptions_t* options,
                 const char* key, size_t keylen, const char* val, size_t vallen,
                 char** errptr) {
  SaveError(errptr,
            db->rep->Put(options->rep, Slice(key, keylen), Slice(val, vallen)));
}

// Default implementations of convenience methods that subclasses of DB
// can call if they wish
Status DB::Put(const WriteOptions& opt, const Slice& key, const Slice& value) {
  WriteBatch batch;
  batch.Put(key, value);
  return Write(opt, &batch);
}

Status DBImpl::Write(const WriteOptions& options, WriteBatch* updates) {
  Writer w(&mutex_);
  w.batch = updates;
  w.sync = options.sync; //用来控制对接的文件系统是否需要刷盘
  w.done = false;

  MutexLock l(&mutex_);
  writers_.push_back(&w); //写队列入队
  while (!w.done && &w != writers_.front()) {
    w.cv.Wait(); // 有别的写在执行并且队列非空，等待唤醒
  }
  if (w.done) { // 所有的写都执行结束
    return w.status;
  }

  // May temporarily unlock and wait.
  Status status = MakeRoomForWrite(updates == nullptr);
  uint64_t last_sequence = versions_->LastSequence();
  Writer* last_writer = &w;
  if (status.ok() && updates != nullptr) {  // nullptr batch is for compactions
    WriteBatch* write_batch = BuildBatchGroup(&last_writer);
    WriteBatchInternal::SetSequence(write_batch, last_sequence + 1);
    last_sequence += WriteBatchInternal::Count(write_batch);

    // Add to log and apply to memtable.  We can release the lock
    // during this phase since &w is currently responsible for logging
    // and protects against concurrent loggers and concurrent writes
    // into mem_.
    {
      mutex_.Unlock();
      status = log_->AddRecord(WriteBatchInternal::Contents(write_batch));
      bool sync_error = false;
      if (status.ok() && options.sync) {
        status = logfile_->Sync();
        if (!status.ok()) {
          sync_error = true;
        }
      }
      if (status.ok()) {
        status = WriteBatchInternal::InsertInto(write_batch, mem_);
      }
      mutex_.Lock();
      if (sync_error) {
        // The state of the log file is indeterminate: the log record we
        // just added may or may not show up when the DB is re-opened.
        // So we force the DB into a mode where all future writes fail.
        RecordBackgroundError(status);
      }
    }
    if (write_batch == tmp_batch_) tmp_batch_->Clear();

    versions_->SetLastSequence(last_sequence);
  }

  while (true) {
    Writer* ready = writers_.front();
    writers_.pop_front();
    if (ready != &w) {
      ready->status = status;
      ready->done = true;
      ready->cv.Signal();
    }
    if (ready == last_writer) break;
  }

  // Notify new head of write queue
  if (!writers_.empty()) {
    writers_.front()->cv.Signal();
  }

  return status;
}
```

# 三、**基本数据结构和算法**

①　跳表

②　LSMT

③　BloomFilter

### 内存分配算法

# 四、**内存结构**

①　MemTable

# 五、**磁盘结构**

①　SSTable

# 六、**compation详解**

# 七、快照原理

快照设计：

所有的读写操作都带版本信息，对于leveldb的读写来说，正常的读写都是默认在最新的快照id的快照上操作的


# 八、**语言体会**

# 九、类设计

## leveldb的抽象

## 迭代器的实现

## 类型转化的实践
