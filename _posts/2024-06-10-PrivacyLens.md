---
layout: post
title: "PrivacyLens Presented at PETS"
featured-img: privacylens.png
mathjax: true
category: Papers
---

[![PrivacyLens Video](http://img.youtube.com/vi/AVwlvuJTjHI/0.jpg)](https://www.youtube.com/watch?v=AVwlvuJTjHI "PrivacyLens")

Internet-connected cameras support many useful home monitoring and health applications. However, these same cameras indiscriminately capture sensitive and Personally Identifiable Information (PII), limiting their acceptance in certain settings, such as the home. Prior works removed Region of Interest (ROI) to secure images and improve privacy. However, the methods that rely solely on RGB information to find persons are susceptible to environmental and lighting conditions, causing them to fail and leak PII. From our deployment study, nearly half of the images containing persons had a PII leakage when using RGB-only methods. Furthermore, ROI removal is often performed off-device, requiring the server performing these operations to be trustworthy. This work presents the PrivacyLens system, where with the addition of thermal sensing, our system has a significantly enhanced ability to find persons in RGB images and video and efficiently remove them on the device before any data is stored or transmitted, all while staying under typical IoT power constraints. From our aforementioned deployment study in an office-building atrium, family home, and outdoor park environment, the PrivacyLens prototype effectively removes PII with a sanitization rate of 99.1%. Additionally, PrivacyLens can use its embedded GPU to generate on-device features for downstream CV/ML tasks, as shown in three illustrative applications, further reducing the collection and storage of PII.

[DOI](https://doi.org/10.56553/popets-2024-0146) [![pdf](/assets/icons16/pdf-icon.png)]({{ BASE_PATH }}/assets/pdf/Iravantchi24PrivacyLens.pdf)