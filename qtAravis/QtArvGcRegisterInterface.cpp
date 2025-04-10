QByteArray QtArvGcRegister::read() const {
    return port()->read(address(), length());
}

void QtArvGcRegister::write(const QByteArray& data) {
    port()->write(address(), data);
}

quint64 QtArvGcRegister::address() const {
    return m_address ? m_address->toUInt64() : 0;
}

quint64 QtArvGcRegister::length() const {
    return m_length ? m_length->toUInt64() : 1;
}
