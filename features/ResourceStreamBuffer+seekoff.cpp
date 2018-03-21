FEATURE ResourceStreamBuffer.h/Impl
// Implement 'seekoff()' to support 'seekg()' calls.
// E.g., OpenSceneGraph ImageIO plugin uses 'seekg()'.
// Topic: How to implement custom std::streambuf's seekoff()?
// Source: https://stackoverflow.com/a/46068920
std::streampos seekoff(
    std::streamoff off,
    std::ios_base::seekdir dir,
    std::ios_base::openmode which = std::ios_base::in
) {
    if (dir == std::ios_base::cur)
        this->gbump(off);
    else if (dir == std::ios_base::end)
        this->setg(this->eback(), this->egptr() + off, this->egptr());
    else if (dir == std::ios_base::beg)
        this->setg(this->eback(), this->eback() + off, this->egptr());
    return this->gptr() - this->eback();
}
