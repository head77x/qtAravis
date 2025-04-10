QString QtArvGcStructEntry::nodeName() const {
    return "StructEntry";
}

qint64 QtArvGcStructEntry::intValue() const {
    auto* parentReg = dynamic_cast<QtArvGcRegisterInterface*>(parentNode());
    if (!parentReg) return 0;

    QByteArray raw = parentReg->read();
    // 마스킹 계산
    int lsb = m_lsb ? m_lsb->toInt() : 0;
    int msb = m_msb ? m_msb->toInt() : 31;
    bool isSigned = m_sign && m_sign->toString() == "Signed";
    int width = qAbs(msb - lsb) + 1;
    quint64 value = 0;
    memcpy(&value, raw.constData(), qMin(raw.size(), 8));
    value = (value >> qMin(lsb, msb)) & ((1ULL << width) - 1);
    if (isSigned && (value & (1ULL << (width - 1))))
        return static_cast<qint64>(value | ~((1ULL << width) - 1)); // 2's complement
    return static_cast<qint64>(value);
}
