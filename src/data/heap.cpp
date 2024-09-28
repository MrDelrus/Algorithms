namespace utils {

template <typename T, typename Comparator = std::less<T>>
class Heap {
public:
  Heap() = default;
  void Insert(const T& object) {
    data_.push_back(object);
    SiftUp_(data_.size() - 1);
  }
  template <class... Args>
  void Emplace(Args&&... args) {
    data_.emplace_back(std::forward<Args>(args)...);
    SiftUp_(data_.size() - 1);
  }
  void Pop() {
    Swap_(0, data_.size() - 1);
    data_.pop_back();
    SiftDown_(0);
  }
  T& Top() {
    return data_[0];
  }
  const T& Top() const {
    return data_[0];
  }
  bool Empty() const {
    return data_.empty();
  }
private:
  void SiftUp_(int index) {
    while (index != 0) {
      size_t indexParent = GetParent_(index);
      if (!comparator_(data_[index], data_[indexParent])) {
        break;
      }
      Swap_(index, indexParent);
      index = indexParent;
    }
  }
  void SiftDown_(int index) {
    while (GetLeft_(index) < data_.size()) {
      size_t indexChild = GetLeft_(index);
      if (GetRight_(index) < data_.size() && comparator_(data_[GetRight_(index)], data_[GetLeft_(index)])) {
        indexChild = GetRight_(index);
      }
      if (comparator_(data_[index], data_[indexChild])) {
        break;
      }
      Swap_(index, indexChild);
      index = indexChild;
    }
  }
private:
  void Swap_(size_t indexFirst, size_t indexSecond) {
    std::swap(data_[indexFirst], data_[indexSecond]);
  }
  static size_t GetParent_(size_t index) {
    return (index - 1) / 2;
  }
  static size_t GetLeft_(size_t index) {
    return 2 * index + 1;
  }
  static size_t GetRight_(size_t index) {
    return 2 * index + 2;
  }
private:
  std::vector<T> data_;
  Comparator comparator_;
};

}  // namespace utils
